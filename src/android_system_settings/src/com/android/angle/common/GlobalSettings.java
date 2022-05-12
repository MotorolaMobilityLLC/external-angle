/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.android.angle.common;

import android.content.ContentResolver;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.provider.Settings;
import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class GlobalSettings
{

    private final String TAG = this.getClass().getSimpleName();

    private Context mContext;
    private List<PackageInfo> mInstalledPkgs         = new ArrayList<>();
    private List<String> mGlobalSettingsDriverPkgs   = new ArrayList<>();
    private List<String> mGlobalSettingsDriverValues = new ArrayList<>();
    private List<String> mGlobalDeferlist            = new ArrayList<>();

    /*
     * Modes of applying the deferlist to the per-application switch (i.e. the
     * "angle_gl_driver_selection_*" settings).  Most devices will not do anything
     * (i.e. DEFERLIST_MODE_NA).  While a device is transitioning from using a legacy driver to
     * using ANGLE, the following modes can be used to defer the use of ANGLE until bugs are fixed.
     *
     * NOTE: the set of modes can grow over time, as we identify new needs.
     */
    // ANGLE deferlist not applicable.  For devices where ANGLE is either: 1) not installed; 2) is
    // not the system driver; 3) is the system driver and there is no legacy driver
    private static final int DEFERLIST_MODE_NA = 0;
    // ANGLE deferlist replaces the existing settings at first boot, and then doesn't change them
    private static final int DEFERLIST_MODE_REPLACE = 1;
    // ANGLE deferlist is merged into the existing settings at first boot, and then doesn't change
    // them
    private static final int DEFERLIST_MODE_MERGE = 2;

    private static final int kDesiredDeferlistMode = DEFERLIST_MODE_REPLACE;

    GlobalSettings(Context context, List<PackageInfo> installedPkgs)
    {
        mContext = context;

        setInstalledPkgs(installedPkgs);
    }

    static void clearAllGlobalSettings(Context context)
    {
        // angle_gl_driver_all_angle
        updateAllUseAngle(context, false);
        // show_angle_in_use_dialog_box
        updateShowAngleInUseDialog(context, false);
        // angle_gl_driver_selection_pkgs, angle_gl_driver_selection_values
        ContentResolver contentResolver = context.getContentResolver();
        Settings.Global.putString(contentResolver,
                context.getString(R.string.global_settings_driver_selection_pkgs), "\"\"");
        Settings.Global.putString(contentResolver,
                context.getString(R.string.global_settings_driver_selection_values), "\"\"");

        // For completeness, we'll clear the angle_debug_package, but we don't allow setting
        // it via the APK (currently)
        Settings.Global.putString(contentResolver,
                context.getString(R.string.global_settings_angle_debug_package), "");

        // Skip angle_deferlist; not updatable via Developer Options
    }

    Boolean getAllUseAngle()
    {
        ContentResolver contentResolver = mContext.getContentResolver();
        try
        {
            int allUseAngle = Settings.Global.getInt(
                    contentResolver, mContext.getString(R.string.global_settings_driver_all_angle));
            return (allUseAngle == 1);
        }
        catch (Settings.SettingNotFoundException e)
        {
            return false;
        }
    }

    Boolean getShowAngleInUseDialogBox()
    {
        ContentResolver contentResolver = mContext.getContentResolver();
        try
        {
            int showAngleInUseDialogBox = Settings.Global.getInt(contentResolver,
                    mContext.getString(R.string.global_settings_show_angle_in_use_dialog_box));
            return (showAngleInUseDialogBox == 1);
        }
        catch (Settings.SettingNotFoundException e)
        {
            return false;
        }
    }

    static void updateAllUseAngle(Context context, Boolean allUseAngle)
    {
        ContentResolver contentResolver = context.getContentResolver();
        Settings.Global.putInt(contentResolver,
                context.getString(R.string.global_settings_driver_all_angle), allUseAngle ? 1 : 0);
    }

    static void updateShowAngleInUseDialog(Context context, Boolean showAngleInUseDialog)
    {
        ContentResolver contentResolver = context.getContentResolver();
        Settings.Global.putInt(contentResolver,
                context.getString(R.string.global_settings_show_angle_in_use_dialog_box),
                showAngleInUseDialog ? 1 : 0);
    }

    static void updateAngleDeferlist(Context context, String packageNames, String driverNames)
    {
        // Write the deferlist to a setting so that it survives reboots
        ContentResolver contentResolver = context.getContentResolver();
        Settings.Global.putString(contentResolver,
                context.getString(R.string.global_settings_angle_deferlist), packageNames);

        // Depending on the device's current and desired deferlist mode, potentially transition to
        // the desired mode, which may involve changing the "angle_gl_driver_selection_*" settings,
        // based on the deferlist packages coming from the packageNames and driverNames parameters.
        int currentDeferlistMode = DEFERLIST_MODE_NA;
        try
        {
            currentDeferlistMode = Settings.Global.getInt(
                contentResolver,
                context.getString(R.string.global_settings_angle_deferlist_mode));
        }
        catch (Settings.SettingNotFoundException e)
        {
            // This is likely a newly-flashed system, with a non-existent setting; assume NA
            currentDeferlistMode = DEFERLIST_MODE_NA;
        }
        switch (kDesiredDeferlistMode)
        {
            case DEFERLIST_MODE_NA:
                // Do nothing
                break;
            case DEFERLIST_MODE_REPLACE:
                // Replace the existing per-application switch settings
                if (currentDeferlistMode != kDesiredDeferlistMode)
                {
                    Settings.Global.putString(contentResolver,
                        context.getString(R.string.global_settings_driver_selection_pkgs),
                        packageNames);
                    Settings.Global.putString(contentResolver,
                        context.getString(R.string.global_settings_driver_selection_values),
                        driverNames);
                }
                break;
            case DEFERLIST_MODE_MERGE:
                // TODO: implement this when needed (b/224558229)
                break;
            default:
                // Do nothing
                break;
        }
        // Set the device's current mode to the desired mode
        Settings.Global.putInt(contentResolver,
            context.getString(R.string.global_settings_angle_deferlist_mode),
            kDesiredDeferlistMode);
    }

    void updatePkg(String pkgName, String driver)
    {
        int pkgIndex = getGlobalSettingsPkgIndex(pkgName);

        if (!isValidDiverValue(driver))
        {
            Log.e(TAG, "Attempting to update a PKG with an invalid driver: '" + driver + "'");
            return;
        }

        String defaultDriver = mContext.getString(R.string.default_driver);
        if (driver.equals(defaultDriver))
        {
            if (pkgIndex >= 0)
            {
                // We only store global settings for driver values other than the default
                mGlobalSettingsDriverPkgs.remove(pkgIndex);
                mGlobalSettingsDriverValues.remove(pkgIndex);
            }
        }
        else
        {
            if (pkgIndex >= 0)
            {
                mGlobalSettingsDriverValues.set(pkgIndex, driver);
            }
            else
            {
                mGlobalSettingsDriverPkgs.add(pkgName);
                mGlobalSettingsDriverValues.add(driver);
            }
        }

        writeGlobalSettings();
    }

    String getDriverForPkg(String pkgName)
    {
        int pkgIndex = getGlobalSettingsPkgIndex(pkgName);

        if (pkgIndex >= 0)
        {
            return mGlobalSettingsDriverValues.get(pkgIndex);
        }

        return null;
    }

    void setInstalledPkgs(List<PackageInfo> installedPkgs)
    {
        mInstalledPkgs = installedPkgs;

        updateGlobalSettings();
    }

    private void updateGlobalSettings()
    {
        readGlobalSettings();

        validateGlobalSettings();

        writeGlobalSettings();
    }

    private void readGlobalSettings()
    {
        mGlobalSettingsDriverPkgs = getGlobalSettingsString(
                mContext.getString(R.string.global_settings_driver_selection_pkgs));
        mGlobalSettingsDriverValues = getGlobalSettingsString(
                mContext.getString(R.string.global_settings_driver_selection_values));
        mGlobalDeferlist = getGlobalSettingsString(
                mContext.getString(R.string.global_settings_angle_deferlist));
    }

    private List<String> getGlobalSettingsString(String globalSetting)
    {
        List<String> valueList;
        ContentResolver contentResolver = mContext.getContentResolver();
        String settingsValue            = Settings.Global.getString(contentResolver, globalSetting);

        if (settingsValue != null)
        {
            valueList = new ArrayList<>(Arrays.asList(settingsValue.split(",")));
        }
        else
        {
            valueList = new ArrayList<>();
        }

        return valueList;
    }

    private void writeGlobalSettings()
    {
        String driverPkgs   = String.join(",", mGlobalSettingsDriverPkgs);
        String driverValues = String.join(",", mGlobalSettingsDriverValues);

        ContentResolver contentResolver = mContext.getContentResolver();
        Settings.Global.putString(contentResolver,
                mContext.getString(R.string.global_settings_driver_selection_pkgs), driverPkgs);
        Settings.Global.putString(contentResolver,
                mContext.getString(R.string.global_settings_driver_selection_values), driverValues);
    }

    private void validateGlobalSettings()
    {
        // Verify lengths
        if (mGlobalSettingsDriverPkgs.size() != mGlobalSettingsDriverValues.size())
        {
            // The lengths don't match, so clear the values out and rebuild later.
            mGlobalSettingsDriverPkgs.clear();
            mGlobalSettingsDriverValues.clear();
            return;
        }

        String defaultDriver = mContext.getString(R.string.default_driver);
        // Use a temp list, since we're potentially modifying the original list.
        List<String> globalSettingsDriverPkgs = new ArrayList<>(mGlobalSettingsDriverPkgs);
        for (String pkgName : globalSettingsDriverPkgs)
        {
            // Remove any uninstalled packages.
            if (!isPkgInstalled(pkgName) && !isPkgInDeferlist(pkgName))
            {
                removePkgFromGlobalSettings(pkgName);
            }
            // Remove any packages with invalid driver values
            else if (!isValidDiverValue(getDriverForPkg(pkgName)))
            {
                removePkgFromGlobalSettings(pkgName);
            }
            // Remove any packages with the 'default' driver selected
            else if (defaultDriver.equals(getDriverForPkg(pkgName)))
            {
                removePkgFromGlobalSettings(pkgName);
            }
        }
    }

    private void removePkgFromGlobalSettings(String pkgName)
    {
        int pkgIndex = getGlobalSettingsPkgIndex(pkgName);

        mGlobalSettingsDriverPkgs.remove(pkgIndex);
        mGlobalSettingsDriverValues.remove(pkgIndex);
    }

    private int getGlobalSettingsPkgIndex(String pkgName)
    {
        for (int pkgIndex = 0; pkgIndex < mGlobalSettingsDriverPkgs.size(); pkgIndex++)
        {
            if (mGlobalSettingsDriverPkgs.get(pkgIndex).equals(pkgName))
            {
                return pkgIndex;
            }
        }

        return -1;
    }

    private Boolean isPkgInstalled(String pkgName)
    {
        for (PackageInfo pkg : mInstalledPkgs)
        {
            if (pkg.packageName.equals(pkgName))
            {
                return true;
            }
        }

        return false;
    }

    private Boolean isPkgInDeferlist(String pkgName)
    {
        List<String> globalSettingsDeferlist = new ArrayList<>(mGlobalDeferlist);
        for (String pkg : globalSettingsDeferlist)
        {
            if (pkg.equals(pkgName))
            {
                return true;
            }
        }

        return false;
    }

    private Boolean isValidDiverValue(String driverValue)
    {
        CharSequence[] drivers = mContext.getResources().getStringArray(R.array.driver_values);

        for (CharSequence driver : drivers)
        {
            if (driverValue.equals(driver.toString()))
            {
                return true;
            }
        }

        return false;
    }
}
