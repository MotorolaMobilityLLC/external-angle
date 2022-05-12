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

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.ContentObserver;
import android.net.Uri;
import android.os.Bundle;
import android.os.SystemProperties;
import android.os.Handler;
import android.provider.Settings;
import android.util.Log;

import androidx.preference.PreferenceManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;

public class Receiver extends BroadcastReceiver
{

    private static final String TAG              = "AngleReceiver";
    private static final String ANGLE_RULES_FILE = "a4a_rules.json";

    // System properties related to ANGLE and legacy GLES graphics drivers.
    private static final String PROPERTY_EGL_SYSTEM_DRIVER = "ro.hardware.egl";
    private static final String PROPERTY_EGL_LEGACY_DRIVER = "ro.hardware.egl_legacy";
    private static final String ANGLE_DRIVER_NAME = "angle";

    @Override
    public void onReceive(Context context, Intent intent)
    {
        String action = intent.getAction();
        Log.v(TAG, "Received intent: '" + action + "'");

        if (action.equals(context.getString(R.string.intent_angle_for_android_toast_message)))
        {
            Bundle results = getResultExtras(true);
            results.putString(context.getString(R.string.intent_key_a4a_toast_message),
                    context.getString(R.string.angle_in_use_toast_message));
        }
        else
        {
            // Process the deferlist only if both: 1) ANGLE is the system driver; 2) there is also a
            // legacy driver:
            final String eglSystemDriver = SystemProperties.get(PROPERTY_EGL_SYSTEM_DRIVER);
            if (!eglSystemDriver.equals(ANGLE_DRIVER_NAME))
            {
                return;
            }
            final String eglLegacyDriver = SystemProperties.get(PROPERTY_EGL_LEGACY_DRIVER);
            if (eglLegacyDriver.isEmpty() || eglSystemDriver.equals(eglLegacyDriver))
            {
                return;
            }

            String jsonStr = loadRules(context);
            parseDeferlist(context, jsonStr);

            updateDeveloperOptionsWatcher(context);
        }
    }

    /*
     * Open the rules file and pull all the JSON into a string
     */
    private String loadRules(Context context)
    {
        String jsonStr = null;

        try
        {
            InputStream rulesStream = context.getAssets().open(ANGLE_RULES_FILE);
            int size                = rulesStream.available();
            byte[] buffer           = new byte[size];
            rulesStream.read(buffer);
            rulesStream.close();
            jsonStr = new String(buffer, "UTF-8");
        }
        catch (IOException ioe)
        {
            Log.e(TAG, "Failed to open " + ANGLE_RULES_FILE + ": ", ioe);
        }

        return jsonStr;
    }

    /*
     * Parse the default deferlist from a json file, and convert it into the following
     * comma-separated settings:
     * - "angle_gl_driver_selection_pkgs"
     * - "angle_gl_driver_selection_values"
     */
    public void parseDeferlist(Context context, String rulesJSON)
    {
        StringBuilder packageNames = new StringBuilder();
        StringBuilder driverNames = new StringBuilder();

        try
        {
            JSONObject jsonObj = new JSONObject(rulesJSON);
            JSONArray rules    = jsonObj.getJSONArray("Rules");
            if (rules == null)
            {
                Log.e(TAG, "No Rules in " + ANGLE_RULES_FILE);
                return;
            }
            for (int i = 0; i < rules.length(); i++)
            {
                JSONObject rule = rules.getJSONObject(i);
                JSONArray apps  = rule.optJSONArray("Applications");
                if (apps == null)
                {
                    Log.v(TAG, "Skipping Rules entry with no Applications");
                    continue;
                }
                for (int j = 0; j < apps.length(); j++)
                {
                    JSONObject app = apps.optJSONObject(j);
                    String appName = app.optString("AppName");
                    if ((appName == null) || appName.isEmpty())
                    {
                        Log.e(TAG, "Invalid AppName: '" + appName + "'");
                    }
                    if (!packageNames.toString().isEmpty())
                    {
                        packageNames.append(",");
                        driverNames.append(",");
                    }
                    packageNames.append(appName);
                    driverNames.append("native");
                }
            }
            Log.v(TAG, "Parsed the following deferlist package names from " + ANGLE_RULES_FILE
                  + ": " + packageNames);
        }
        catch (JSONException je)
        {
            Log.e(TAG, "Error when parsing angle deferlist JSON: ", je);
            return;
        }

        GlobalSettings.updateAngleDeferlist(context, packageNames.toString(),
            driverNames.toString());
    }

    static void updateAllUseAngle(Context context)
    {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        String allUseAngleKey   = context.getString(R.string.pref_key_all_angle);
        boolean allUseAngle     = prefs.getBoolean(allUseAngleKey, false);

        GlobalSettings.updateAllUseAngle(context, allUseAngle);

        Log.v(TAG, "All PKGs use ANGLE set to: " + allUseAngle);
    }

    static void updateShowAngleInUseDialogBox(Context context)
    {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        String showAngleInUseDialogBoxKey =
                context.getString(R.string.pref_key_angle_in_use_dialog);
        boolean showAngleInUseDialogBox = prefs.getBoolean(showAngleInUseDialogBoxKey, false);

        GlobalSettings.updateShowAngleInUseDialog(context, showAngleInUseDialogBox);

        Log.v(TAG, "Show 'ANGLE In Use' dialog box set to: " + showAngleInUseDialogBox);
    }

    /**
     * When Developer Options are disabled, reset all of the global settings back to their defaults.
     */
    private static void updateDeveloperOptionsWatcher(Context context)
    {
        Uri settingUri = Settings.Global.getUriFor(Settings.Global.DEVELOPMENT_SETTINGS_ENABLED);

        ContentObserver developerOptionsObserver = new ContentObserver(new Handler()) {
            @Override
            public void onChange(boolean selfChange)
            {
                super.onChange(selfChange);

                boolean developerOptionsEnabled =
                        (1
                                == Settings.Global.getInt(context.getContentResolver(),
                                        Settings.Global.DEVELOPMENT_SETTINGS_ENABLED, 0));

                Log.v(TAG, "Developer Options enabled value changed: "
                                   + "developerOptionsEnabled = " + developerOptionsEnabled);

                /*
                 * NOTE: We DO NOT want to clear these when ANGLE is system driver
                 *
                 * TODO: We need to be able to query the service to known when to do this
                 *
                if (!developerOptionsEnabled)
                {
                    // Reset the necessary settings to their defaults.
                    SharedPreferences.Editor editor =
                            PreferenceManager.getDefaultSharedPreferences(context).edit();
                    editor.clear();
                    editor.apply();
                    GlobalSettings.clearAllGlobalSettings(context);
                }
                */
            }
        };

        context.getContentResolver().registerContentObserver(
                settingUri, false, developerOptionsObserver);
        developerOptionsObserver.onChange(true);
    }
}
