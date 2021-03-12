// GENERATED FILE - DO NOT EDIT.
// Generated by gen_restricted_traces.py using data from restricted_traces.json
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// restricted_traces_autogen: Types and enumerations for trace tests.

#ifndef ANGLE_RESTRICTED_TRACES_H_
#define ANGLE_RESTRICTED_TRACES_H_

#include <KHR/khrplatform.h>
#include <cstdint>
#include <vector>

// See util/util_export.h for details on import/export labels.
#if !defined(ANGLE_TRACE_EXPORT)
#    if defined(_WIN32)
#        if defined(ANGLE_TRACE_IMPLEMENTATION)
#            define ANGLE_TRACE_EXPORT __declspec(dllexport)
#        else
#            define ANGLE_TRACE_EXPORT __declspec(dllimport)
#        endif
#    elif defined(__GNUC__)
#        define ANGLE_TRACE_EXPORT __attribute__((visibility("default")))
#    else
#        define ANGLE_TRACE_EXPORT
#    endif
#endif  // !defined(ANGLE_TRACE_EXPORT)

#if !defined(ANGLE_TRACE_LOADER_EXPORT)
#    if defined(_WIN32)
#        if defined(ANGLE_TRACE_LOADER_IMPLEMENTATION)
#            define ANGLE_TRACE_LOADER_EXPORT __declspec(dllexport)
#        else
#            define ANGLE_TRACE_LOADER_EXPORT __declspec(dllimport)
#        endif
#    elif defined(__GNUC__)
#        define ANGLE_TRACE_LOADER_EXPORT __attribute__((visibility("default")))
#    else
#        define ANGLE_TRACE_LOADER_EXPORT
#    endif
#endif  // !defined(ANGLE_TRACE_LOADER_EXPORT)

namespace trace_angle
{
using GenericProc = void (*)();
using LoadProc    = GenericProc(KHRONOS_APIENTRY *)(const char *);
ANGLE_TRACE_LOADER_EXPORT void LoadGLES(LoadProc loadProc);
}  // namespace trace_angle

namespace angle
{
enum class RestrictedTraceID
{
    aliexpress,
    among_us,
    angry_birds_2_1500,
    arena_of_valor,
    asphalt_8,
    brawl_stars,
    bus_simulator_indonesia,
    candy_crush_500,
    car_parking_multiplayer,
    clash_of_clans,
    clash_royale,
    cod_mobile,
    coin_master,
    dragon_ball_legends,
    efootball_pes_2021,
    egypt_1500,
    eight_ball_pool,
    extreme_car_driving_simulator,
    fallout_shelter_online,
    fate_grand_order,
    fifa_mobile,
    free_fire,
    google_maps,
    happy_color,
    hay_day,
    hearthstone,
    hill_climb_racing,
    junes_journey,
    kartrider_rush,
    klondike_adventures,
    lego_legacy,
    lineage_m,
    magic_tiles_3,
    manhattan_10,
    manhattan_31,
    marvel_contest_of_champions,
    messenger_lite,
    minecraft,
    mobile_legends,
    nba2k20_800,
    one_punch_man,
    plants_vs_zombies_2,
    pubg_mobile_lite,
    raid_shadow_legends,
    real_commando_secret_mission,
    real_gangster_crime,
    rise_of_kingdoms,
    romancing_saga,
    rope_hero_vice_town,
    saint_seiya_awakening,
    shadow_fight_2,
    sniper_3d,
    standoff_2,
    subway_surfers,
    talking_tom_hero_dash,
    temple_run_2,
    temple_run_300,
    trex_200,
    whatsapp,
    world_of_tanks_blitz,
    world_war_doh,
    worms_zone_io,
    InvalidEnum,
    EnumCount = InvalidEnum
};

using ReplayFunc           = void (*)(uint32_t);
using ResetFunc            = void (*)();
using SetupFunc            = void (*)();
using DecompressFunc       = uint8_t *(*)(const std::vector<uint8_t> &);
using SetBinaryDataDirFunc = void (*)(const char *);

static constexpr size_t kTraceInfoMaxNameLen = 32;

static constexpr uint32_t kDefaultReplayContextClientMajorVersion = 3;
static constexpr uint32_t kDefaultReplayContextClientMinorVersion = 1;

struct TraceInfo
{
    uint32_t contextClientMajorVersion;
    uint32_t contextClientMinorVersion;
    uint32_t startFrame;
    uint32_t endFrame;
    uint32_t drawSurfaceWidth;
    uint32_t drawSurfaceHeight;
    char name[kTraceInfoMaxNameLen];
};

using DecompressCallback = uint8_t *(*)(const std::vector<uint8_t> &);

ANGLE_TRACE_EXPORT const TraceInfo &GetTraceInfo(RestrictedTraceID traceID);
ANGLE_TRACE_EXPORT void ReplayFrame(RestrictedTraceID traceID, uint32_t frameIndex);
ANGLE_TRACE_EXPORT void ResetReplay(RestrictedTraceID traceID);
ANGLE_TRACE_EXPORT void SetupReplay(RestrictedTraceID traceID);
ANGLE_TRACE_EXPORT void SetBinaryDataDir(RestrictedTraceID traceID, const char *dataDir);
ANGLE_TRACE_EXPORT void SetBinaryDataDecompressCallback(RestrictedTraceID traceID,
                                                        DecompressCallback callback);
}  // namespace angle

#endif  // ANGLE_RESTRICTED_TRACES_H_
