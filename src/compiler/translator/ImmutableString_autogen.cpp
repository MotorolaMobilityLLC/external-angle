// GENERATED FILE - DO NOT EDIT.
// Generated by gen_builtin_symbols.py using data from builtin_variables.json and
// builtin_function_declarations.txt.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ImmutableString_autogen.cpp: Wrapper for static or pool allocated char arrays, that are
// guaranteed to be valid and unchanged for the duration of the compilation. Implements
// mangledNameHash using perfect hash function from gen_builtin_symbols.py

#include "compiler/translator/ImmutableString.h"

std::ostream &operator<<(std::ostream &os, const sh::ImmutableString &str)
{
    return os.write(str.data(), str.length());
}

#if defined(_MSC_VER)
#    pragma warning(disable : 4309)  // truncation of constant value
#endif

namespace
{

constexpr int mangledkT1[] = {28,   3723, 1475, 371,  51,   3462, 1683, 2358, 3960, 3760,
                              2533, 2942, 2587, 1686, 466,  832,  1198, 860,  3747, 824,
                              946,  743,  1301, 3888, 1189, 1813, 3864, 248,  3590, 3448,
                              1379, 196,  1988, 2577, 1764, 270,  376};
constexpr int mangledkT2[] = {2798, 3904, 2564, 1178, 3278, 628,  2610, 1987, 3024, 1954,
                              2499, 12,   3392, 2914, 794,  3806, 3980, 2527, 3362, 3980,
                              1226, 3423, 713,  1825, 1062, 1687, 1758, 3010, 2151, 2612,
                              1189, 1755, 1372, 2634, 1830, 448,  2730};
constexpr int mangledkG[]  = {
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    636,  0,    0,    0,    1557, 0,    1759, 0,    632,  3658, 0,    0,    0,    144,  0,    0,
    0,    0,    3618, 0,    0,    0,    0,    0,    2168, 0,    0,    0,    0,    1102, 557,  0,
    0,    0,    0,    0,    0,    1245, 0,    398,  0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    3953, 0,    0,    0,    2259, 3302, 0,    591,  0,    0,    0,    0,    0,    553,
    0,    0,    609,  831,  3786, 0,    0,    372,  0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    3406, 0,
    2363, 0,    0,    0,    0,    0,    3243, 1272, 0,    0,    1278, 991,  3862, 3509, 1810, 0,
    3136, 0,    0,    0,    857,  3599, 0,    0,    0,    0,    3094, 0,    1236, 556,  3393, 0,
    3894, 0,    0,    0,    0,    0,    0,    0,    0,    3743, 0,    0,    0,    2585, 1847, 0,
    1135, 0,    1030, 0,    0,    0,    0,    3773, 0,    1444, 0,    2042, 0,    0,    0,    56,
    3120, 0,    0,    0,    272,  0,    3168, 464,  0,    488,  3598, 0,    0,    0,    0,    3508,
    4016, 0,    0,    0,    2057, 0,    303,  3318, 0,    1981, 815,  1326, 0,    0,    0,    0,
    3622, 0,    0,    202,  3694, 0,    1733, 0,    0,    808,  0,    0,    0,    0,    956,  0,
    1368, 0,    3736, 0,    0,    3065, 1245, 0,    0,    0,    409,  0,    0,    0,    2606, 0,
    3661, 2311, 0,    3811, 1393, 1391, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3284, 2986, 0,    0,    226,  0,    0,    0,    0,    0,    0,    0,    0,    2555, 0,
    0,    0,    0,    0,    2444, 0,    0,    0,    2337, 3002, 0,    646,  0,    0,    0,    0,
    0,    0,    1202, 0,    0,    0,    0,    0,    0,    0,    0,    293,  0,    0,    0,    0,
    3423, 3236, 3983, 0,    485,  0,    0,    0,    0,    836,  0,    3861, 0,    0,    0,    0,
    2754, 0,    0,    1363, 0,    0,    0,    0,    2604, 3959, 0,    0,    0,    3584, 0,    0,
    0,    3238, 331,  0,    3971, 3592, 2478, 0,    0,    0,    97,   0,    0,    0,    2221, 0,
    3697, 0,    3615, 3611, 318,  1276, 3645, 0,    0,    0,    1633, 0,    743,  0,    0,    3424,
    0,    0,    1881, 0,    0,    0,    604,  0,    555,  3153, 1371, 0,    0,    0,    568,  415,
    0,    0,    341,  3985, 1958, 283,  0,    2405, 2671, 0,    389,  274,  0,    0,    0,    0,
    1016, 0,    0,    0,    0,    3380, 0,    0,    0,    2451, 0,    0,    774,  0,    2750, 0,
    0,    0,    3999, 0,    0,    0,    0,    0,    0,    0,    0,    0,    234,  0,    1147, 0,
    0,    0,    0,    0,    988,  1924, 0,    314,  0,    445,  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    3466, 0,    0,    715,  175,  0,    0,    0,    518,  2012, 0,    2522,
    2864, 0,    154,  60,   1774, 3742, 501,  0,    2699, 1838, 0,    0,    0,    552,  1077, 2775,
    1334, 3788, 3305, 0,    229,  849,  1482, 0,    107,  0,    1677, 0,    3732, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    3430, 0,    271,  2401, 0,    0,    0,    652,  0,    2725,
    358,  2161, 1442, 0,    1868, 0,    0,    0,    0,    0,    1183, 0,    384,  0,    0,    2249,
    1705, 178,  3582, 0,    3088, 0,    0,    616,  0,    0,    0,    0,    846,  1990, 482,  0,
    3531, 1074, 975,  0,    0,    537,  0,    2366, 0,    0,    0,    0,    0,    0,    3815, 616,
    0,    0,    0,    0,    704,  0,    0,    768,  0,    0,    0,    0,    704,  2074, 0,    635,
    0,    0,    2322, 0,    0,    0,    538,  0,    28,   1918, 0,    1461, 344,  0,    1038, 0,
    0,    0,    0,    0,    1588, 0,    1314, 0,    0,    0,    1117, 0,    2514, 2536, 0,    0,
    81,   0,    0,    0,    3382, 0,    3520, 427,  0,    0,    0,    3688, 0,    0,    0,    0,
    3846, 1981, 0,    445,  0,    0,    844,  0,    0,    0,    0,    759,  216,  3985, 191,  0,
    0,    2133, 0,    3502, 0,    0,    0,    2572, 1011, 0,    1716, 0,    481,  0,    2580, 0,
    0,    0,    955,  0,    0,    0,    842,  1305, 0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    3747, 0,    0,    3866, 3432, 3789, 2614, 0,    0,    1923, 0,    0,    0,    0,
    0,    2583, 3179, 2796, 0,    61,   1575, 3,    3054, 0,    2979, 630,  2081, 529,  0,    284,
    758,  0,    0,    0,    0,    0,    0,    0,    372,  0,    0,    305,  2299, 0,    3731, 0,
    0,    0,    3640, 0,    3746, 2579, 399,  0,    0,    1020, 1363, 2635, 1684, 0,    2367, 0,
    0,    3909, 0,    0,    1081, 0,    1058, 422,  0,    3971, 3517, 0,    1065, 0,    0,    0,
    0,    1189, 0,    2997, 444,  0,    3219, 0,    0,    723,  0,    0,    1014, 0,    0,    74,
    0,    0,    0,    3780, 14,   0,    2032, 866,  3987, 2973, 0,    0,    1235, 3759, 0,    0,
    0,    3138, 3507, 0,    114,  3255, 0,    1471, 995,  1199, 1626, 3669, 0,    3314, 393,  0,
    0,    0,    1832, 3337, 0,    0,    0,    0,    0,    0,    0,    0,    0,    2204, 734,  0,
    393,  0,    2329, 0,    1981, 0,    0,    0,    2026, 0,    0,    0,    437,  0,    0,    0,
    705,  154,  197,  0,    3557, 0,    0,    0,    1657, 0,    1767, 8,    0,    0,    0,    1722,
    3584, 57,   0,    3507, 0,    0,    0,    0,    0,    3651, 0,    1919, 0,    0,    0,    1172,
    0,    0,    1227, 722,  1277, 0,    1183, 0,    500,  0,    2072, 0,    0,    0,    2871, 0,
    0,    0,    2718, 0,    0,    0,    3317, 0,    0,    3164, 0,    0,    0,    2978, 0,    0,
    0,    196,  0,    770,  0,    0,    537,  0,    751,  2742, 225,  0,    0,    0,    0,    0,
    261,  0,    611,  487,  662,  1434, 3189, 0,    0,    3148, 718,  0,    0,    0,    3126, 796,
    0,    2077, 0,    0,    3946, 4013, 1625, 1005, 554,  2410, 1953, 49,   0,    0,    0,    3451,
    0,    0,    340,  3639, 0,    1687, 0,    0,    2741, 965,  0,    3674, 0,    2712, 3370, 2753,
    2045, 2445, 3548, 0,    3099, 664,  445,  1524, 934,  0,    2314, 0,    0,    0,    0,    0,
    3208, 0,    925,  124,  2256, 1055, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    1076, 0,    0,    0,    1400, 3126, 603,  0,    1092, 2082, 0,    0,    567,  0,    3705,
    362,  0,    0,    0,    0,    0,    0,    0,    1406, 1460, 0,    2881, 314,  3849, 0,    0,
    2920, 44,   0,    1173, 397,  0,    885,  180,  0,    0,    525,  0,    0,    1131, 0,    0,
    0,    3192, 3324, 3209, 2013, 0,    3919, 0,    0,    1785, 0,    0,    870,  0,    0,    2102,
    0,    1978, 1076, 0,    0,    1864, 0,    0,    1620, 0,    2579, 0,    344,  0,    0,    3232,
    1715, 0,    298,  0,    505,  1546, 3777, 0,    0,    853,  919,  0,    3894, 0,    0,    1955,
    0,    0,    0,    1710, 0,    0,    0,    3585, 1948, 0,    170,  0,    3265, 0,    0,    3925,
    3286, 178,  508,  0,    0,    1196, 0,    0,    0,    1138, 3397, 1717, 0,    3431, 0,    0,
    0,    0,    3071, 0,    120,  0,    3460, 0,    0,    0,    0,    3466, 0,    3130, 0,    0,
    0,    858,  30,   0,    0,    3691, 3536, 2312, 2209, 1296, 0,    2091, 658,  2452, 0,    4014,
    1902, 1272, 0,    1003, 1669, 3654, 0,    1218, 1633, 638,  667,  0,    0,    1151, 0,    677,
    0,    1447, 0,    3861, 0,    0,    761,  2065, 450,  0,    1556, 0,    1384, 0,    0,    315,
    332,  264,  0,    0,    0,    0,    1649, 0,    0,    3828, 303,  1584, 415,  1777, 0,    0,
    0,    2067, 1470, 0,    0,    0,    0,    3062, 0,    1261, 0,    0,    0,    0,    0,    0,
    1340, 2966, 0,    3315, 950,  197,  2666, 3940, 0,    129,  1236, 3708, 0,    3993, 32,   0,
    0,    0,    1150, 1653, 2103, 1568, 739,  0,    3667, 2334, 0,    3510, 3334, 1903, 732,  0,
    0,    0,    726,  0,    1415, 2481, 282,  0,    0,    0,    0,    0,    0,    1942, 0,    0,
    1499, 1825, 0,    2152, 0,    0,    1,    657,  0,    717,  0,    3886, 0,    1702, 0,    0,
    2208, 0,    0,    338,  0,    2928, 0,    125,  3530, 160,  0,    0,    1256, 0,    0,    0,
    0,    3125, 693,  0,    1382, 1328, 0,    0,    0,    0,    0,    0,    1177, 1450, 883,  625,
    1994, 742,  0,    0,    472,  0,    1643, 0,    0,    0,    0,    0,    2545, 81,   0,    0,
    0,    2691, 0,    0,    0,    0,    0,    0,    23,   0,    0,    1485, 1311, 1607, 0,    0,
    0,    2083, 668,  466,  0,    0,    2659, 2370, 593,  1836, 240,  3413, 588,  3216, 1269, 1775,
    3241, 0,    3502, 0,    230,  0,    359,  0,    1551, 0,    0,    688,  3891, 0,    368,  1651,
    0,    1366, 244,  0,    496,  3116, 0,    0,    0,    0,    1953, 0,    1972, 0,    4020, 0,
    0,    0,    0,    0,    1998, 955,  0,    2103, 1870, 0,    2774, 0,    3782, 0,    3032, 0,
    1696, 0,    0,    0,    0,    0,    0,    2076, 0,    0,    0,    0,    438,  2046, 0,    0,
    2470, 0,    115,  0,    2982, 0,    3022, 0,    3493, 0,    3672, 0,    2653, 0,    0,    121,
    0,    0,    525,  0,    633,  3430, 2319, 0,    0,    0,    3029, 3435, 0,    0,    469,  1117,
    3583, 1950, 1809, 1139, 2433, 0,    0,    0,    2078, 0,    1322, 0,    960,  0,    0,    1883,
    0,    16,   0,    0,    1614, 374,  228,  3353, 497,  2183, 0,    1265, 1648, 2924, 719,  2034,
    2883, 0,    0,    0,    1828, 1129, 0,    1089, 0,    148,  1085, 2536, 0,    3280, 0,    0,
    113,  0,    1896, 0,    1466, 0,    0,    0,    660,  0,    0,    0,    1628, 0,    3684, 3561,
    220,  0,    0,    0,    0,    0,    3034, 782,  0,    0,    0,    2703, 0,    0,    3021, 0,
    0,    0,    0,    0,    0,    1879, 328,  0,    0,    0,    124,  0,    331,  0,    1017, 0,
    2989, 0,    1371, 0,    133,  1188, 189,  0,    703,  0,    213,  1868, 0,    0,    1037, 2946,
    70,   1686, 0,    0,    2888, 0,    0,    0,    365,  0,    822,  1311, 0,    469,  3169, 0,
    1069, 0,    0,    1205, 3878, 1739, 0,    2989, 0,    245,  260,  0,    0,    0,    0,    0,
    0,    0,    987,  0,    1378, 0,    1617, 1594, 345,  0,    0,    726,  0,    0,    776,  0,
    0,    0,    582,  1825, 2134, 0,    0,    0,    1914, 0,    0,    1357, 3270, 1047, 0,    0,
    0,    151,  2456, 1354, 0,    480,  609,  0,    0,    0,    0,    664,  527,  0,    2945, 0,
    2457, 348,  21,   502,  1175, 814,  0,    2804, 434,  0,    0,    0,    370,  0,    0,    1599,
    301,  0,    3456, 0,    0,    0,    954,  2817, 0,    1807, 1686, 930,  0,    0,    0,    319,
    0,    2293, 2958, 0,    936,  0,    1794, 0,    0,    3472, 0,    670,  930,  393,  296,  0,
    1853, 1307, 92,   844,  1568, 0,    3424, 0,    1638, 83,   420,  0,    434,  413,  331,  0,
    0,    896,  0,    2277, 3024, 0,    3652, 0,    2236, 712,  1326, 456,  541,  1604, 0,    0,
    1587, 0,    0,    2275, 0,    280,  0,    0,    1392, 995,  0,    636,  1317, 2601, 2303, 0,
    0,    0,    1862, 0,    0,    0,    0,    0,    0,    403,  0,    989,  1752, 1385, 0,    575,
    1268, 0,    1889, 0,    0,    1026, 2164, 3493, 0,    0,    0,    0,    2381, 0,    46,   662,
    3448, 0,    369,  1057, 0,    1549, 2041, 0,    1216, 0,    1658, 0,    1175, 0,    3132, 0,
    1500, 446,  0,    0,    3682, 0,    0,    0,    2067, 1095, 0,    0,    2448, 0,    588,  1983,
    1632, 176,  0,    0,    293,  3959, 0,    1044, 1535, 0,    0,    0,    0,    2000, 0,    2770,
    0,    1641, 236,  3657, 1731, 713,  1514, 2019, 0,    990,  0,    425,  0,    0,    0,    0,
    0,    566,  0,    3274, 0,    0,    0,    217,  3682, 814,  1493, 0,    3354, 0,    0,    0,
    330,  2790, 41,   3529, 823,  0,    0,    0,    0,    1875, 0,    0,    0,    1392, 906,  0,
    3243, 852,  0,    0,    3331, 851,  1844, 3697, 192,  1500, 0,    0,    824,  0,    0,    0,
    0,    3490, 3967, 1535, 0,    0,    3029, 0,    0,    749,  1419, 0,    0,    0,    0,    0,
    0,    3896, 1765, 3675, 0,    1920, 755,  0,    0,    1743, 3076, 3583, 944,  3500, 3347, 1239,
    0,    1502, 1211, 0,    0,    3629, 0,    981,  1488, 0,    0,    1469, 3730, 1303, 2828, 1335,
    3822, 0,    1669, 2205, 3316, 0,    0,    296,  1902, 0,    3953, 2981, 3204, 1636, 1135, 1890,
    0,    793,  0,    690,  0,    3419, 651,  0,    777,  0,    3203, 0,    1376, 734,  1992, 831,
    965,  571,  999,  1393, 0,    0,    1974, 323,  0,    2612, 0,    512,  2407, 193,  0,    1992,
    0,    859,  0,    1147, 0,    0,    740,  0,    773,  0,    612,  3184, 860,  0,    1449, 0,
    3299, 0,    1132, 0,    583,  1171, 733,  2202, 2744, 3304, 0,    1967, 0,    0,    167,  1426,
    772,  0,    3156, 0,    0,    0,    846,  809,  0,    0,    0,    0,    454,  1562, 0,    0,
    2749, 0,    0,    821,  1131, 1815, 0,    0,    3248, 0,    2562, 0,    1176, 60,   997,  0,
    781,  2191, 1717, 482,  0,    0,    1239, 0,    327,  790,  3824, 219,  0,    920,  3017, 406,
    1601, 0,    802,  0,    0,    0,    2699, 2298, 311,  2157, 2114, 2705, 0,    0,    0,    0,
    0,    1764, 0,    3238, 0,    751,  917,  3436, 0,    0,    1358, 553,  0,    3235, 3912, 0,
    599,  728,  0,    1614, 0,    2651, 34,   85,   225,  0,    0,    0,    0,    1384, 0,    0,
    888,  1909, 2058, 0,    894,  0,    0,    0,    1732, 464,  968,  0,    1595, 474,  2644, 651,
    0,    1462, 419,  0,    2715, 82,   2657, 0,    0,    0,    708,  3209, 3042, 1875, 3161, 3730,
    0,    2466, 2028, 1058, 2095, 0,    0,    0,    0,    0,    0,    0,    1867, 0,    1857, 925,
    0,    0,    566,  1880, 0,    0,    1491, 2843, 0,    0,    2971, 0,    317,  2253, 3272, 0,
    558,  656,  3319, 1059, 1237, 2193, 122,  0,    1333, 1201, 0,    0,    3028, 2880, 1573, 776,
    0,    3536, 765,  1099, 0,    1908, 2,    0,    0,    3766, 1416, 0,    3456, 0,    0,    725,
    1307, 3418, 1233, 743,  1394, 2714, 497,  3623, 3521, 858,  2532, 0,    1634, 0,    0,    1814,
    2959, 0,    0,    0,    0,    0,    0,    0,    3940, 1208, 0,    0,    0,    1510, 0,    0,
    1608, 902,  0,    3591, 0,    0,    0,    0,    0,    99,   0,    0,    3286, 3488, 1209, 1747,
    218,  2619, 629,  0,    0,    3310, 0,    0,    1523, 2110, 3762, 746,  0,    236,  1536, 1662,
    902,  2828, 0,    0,    938,  0,    0,    0,    514,  0,    611,  0,    0,    853,  0,    998,
    2611, 0,    0,    0,    0,    1689, 0,    0,    0,    0,    2663, 0,    3320, 891,  2514, 443,
    3775, 1997, 2973, 112,  3998, 0,    0,    601,  0,    0,    1075, 1980, 1751, 3735, 0,    3681,
    0,    0,    0,    0,    1094, 0,    1095, 2564, 1487, 0,    2955, 0,    3767, 317,  0,    1580,
    1379, 0,    0,    2202, 0,    0,    2224, 1288, 1811, 0,    190,  0,    0,    0,    2192, 294,
    357,  0,    2941, 0,    3830, 1784, 2348, 0,    1895, 1620, 0,    1519, 413,  0,    0,    0,
    0,    3372, 833,  1220, 0,    0,    634,  0,    0,    0,    1118, 1986, 465,  2886, 0,    0,
    2008, 1054, 0,    2190, 1683, 369,  2271, 1498, 917,  982,  0,    0,    0,    1032, 140,  3517,
    2680, 2601, 127,  1106, 2121, 0,    3086, 0,    0,    0,    0,    0,    395,  573,  0,    475,
    0,    0,    3821, 0,    3820, 603,  469,  2719, 0,    0,    2533, 0,    1871, 1969, 0,    0,
    0,    2023, 0,    0,    2227, 1424, 875,  39,   586,  697,  1669, 0,    495,  0,    780,  0,
    695,  276,  861,  1134, 317,  675,  0,    1259, 3257, 1016, 0,    714,  3429, 0,    1447, 1588,
    0,    0,    0,    0,    632,  1091, 0,    638,  3485, 2187, 2118, 0,    1795, 1680, 818,  0,
    0,    0,    0,    3287, 0,    0,    3788, 0,    3732, 924,  342,  2730, 0,    3330, 1806, 0,
    1370, 0,    3105, 3381, 1047, 428,  2572, 3293, 2193, 0,    1377, 2512, 3140, 512,  0,    0,
    3999, 832,  0,    3395, 2104, 0,    0,    1560, 0,    1692, 755,  0,    2131, 2672, 0,    1227,
    0,    0,    0,    1328, 0,    1843, 0,    0,    1109, 0,    0,    140,  3631, 0,    0,    1836,
    1841, 0,    2901, 2382, 0,    871,  0,    49,   0,    0,    3334, 0,    1077, 0,    118,  2146,
    411,  0,    0,    0,    1004, 497,  0,    0,    54,   779,  3828, 0,    0,    2080, 3606, 592,
    0,    0,    239,  2314, 71,   642,  881,  2439, 8,    1462, 1373, 3882, 1380, 0,    734,  0,
    0,    0,    3850, 3768, 0,    708,  1748, 935,  729,  2084, 0,    0,    1978, 907,  1145, 296,
    3547, 879,  0,    1499, 1920, 1199, 0,    0,    366,  1385, 854,  2414, 0,    0,    3304, 423,
    3111, 1176, 0,    1633, 2241, 2005, 0,    0,    1425, 0,    0,    3630, 1831, 2038, 2164, 0,
    3681, 0,    0,    0,    2616, 0,    0,    0,    0,    2014, 0,    2846, 1790, 2983, 0,    2645,
    0,    551,  3958, 589,  163,  617,  0,    0,    159,  0,    0,    4020, 1666, 0,    0,    0,
    0,    2649, 0,    2278, 898,  0,    3956, 1208, 1127, 197,  526,  0,    24,   3784, 0,    802,
    499,  0,    979,  0,    983,  0,    1187, 0,    662,  3479, 2003, 0,    2882, 0,    641,  3417,
    0,    1918, 0,    782,  1488, 29,   0,    0,    2022, 922,  0,    459,  2949, 470,  0,    275,
    889,  0,    0,    1114, 481,  0,    1248, 0,    830,  3833, 0,    0,    1168, 0,    0,    961,
    4010, 2533, 0,    791,  41,   3451, 3299, 0,    2265, 2087, 2773, 0,    1570, 0,    1802, 1562,
    3715, 0,    3316, 486,  3668, 1536, 771,  918,  3954, 2002, 0,    205,  3614, 2075, 1335, 2005,
    3626, 1043, 535,  0,    0,    3297, 1960, 1241, 0,    0,    0,    0,    1883, 0,    3160, 0,
    1361, 939,  0,    0,    0,    1186, 0,    0,    1816, 1012, 0,    1283, 1974, 0,    0,    3671,
    0,    0,    0,    0,    0,    0,    1056, 0,    0,    3170, 3275, 0,    3621, 0,    0,    3260,
    849,  3515, 3930, 841,  2895, 1812, 1521, 983,  467,  0,    0,    0,    935,  3406, 2045, 1877,
    758,  2137, 0,    1112, 0,    0,    2676, 3705, 2568, 3872, 3537, 3917, 1801, 0,    0,    702,
    0,    0,    0,    692,  60,   0,    309,  3855, 2573, 562,  0,    0,    500,  1243, 2173, 3179,
    3398, 1507, 569,  1538, 2403, 3635, 3190, 2088, 0,    1084, 0,    3621, 2706, 0,    335,  677,
    1625, 924,  0,    0,    0,    3172, 1423, 0,    2965, 0,    0,    340,  3256, 0,    1695, 3325,
    1292, 0,    0,    0,    2502, 1157, 821,  1611, 0,    0,    0,    274,  0,    3967, 3029, 2084,
    1325, 2836, 554,  1310, 0,    2047, 3840, 0,    1046, 2129, 3667, 463,  0,    0,    0,    2302,
    0,    0,    702,  0,    1260, 0,    0,    0,    1666, 112,  1163, 1059, 0,    0,    0,    2074,
    1940, 2277, 113,  0,    0,    0,    0,    3348, 0,    0,    0,    1221, 0,    967,  3642, 0,
    0,    0,    0,    0,    649,  79,   3954, 0,    0,    0,    3190, 0,    1202, 3998, 1366, 0,
    3104, 0,    1483, 1734, 0,    137,  2011, 0,    1786, 0,    1375, 0,    0,    0,    2494, 0,
    0,    3758, 0,    1976, 0,    0,    0,    985,  831,  0,    1219, 1581, 0,    3285, 1678, 0,
    0,    0,    0,    3455, 1779, 0,    0,    0,    3186, 2054, 491,  0,    0,    0,    3514, 0,
    2750, 3279, 3653, 0,    3437, 0,    192,  1154, 2811, 0,    1179, 1825, 2890, 0,    1393, 0,
    3108, 3404, 2368, 917,  134,  0,    0,    0,    171,  0,    0,    0,    1615, 235,  3167, 2698,
    2774, 3235, 123,  3822, 0,    0,    3161, 0,    1622, 0,    0,    1900, 1887, 0,    0,    0,
    0,    3894, 1122, 0,    223,  123,  3272, 3258, 1988, 0,    0,    0,    1432, 1478, 1939, 749,
    1815, 3939, 3130, 3624, 237,  128,  542,  0,    2294, 1653, 1886, 0,    1284, 1890, 715,  1883,
    3261, 0,    181,  206,  0,    576,  1496, 0,    0,    281,  2228, 956,  1561, 1826, 0,    0,
    0,    0,    3280, 2137, 357,  0,    1226, 0,    1228, 0,    3142, 3542, 3421, 0,    0,    0,
    2143, 0,    0,    15,   0,    889,  3698, 0,    0,    0,    566,  2396, 904,  0,    3506, 2681,
    81,   0,    0,    0,    0,    0,    2705, 202,  2876, 3921, 2035, 3667, 101,  0,    0,    0,
    1227, 0,    2277, 0,    0,    354,  415,  2380, 3933, 0,    841,  3972, 1343, 3506, 701,  1742,
    1549, 0,    0,    0,    815,  1085, 1586, 1086, 2698, 1501, 539,  0,    1304, 1389, 1244, 3640,
    0,    0,    422,  2104, 1354, 873,  0,    0,    1750, 4000, 1741, 3393, 1198, 0,    0,    0,
    0,    1698, 1660, 0,    1262, 280,  0,    0,    0,    0,    917,  3030, 0,    0,    1345, 166,
    1819, 1475, 1937, 2117, 0,    885,  1157, 2625, 1827, 2238, 1197, 159,  0,    443,  882,  0,
    1275, 0,    2593, 551,  1462, 0,    0,    3799, 2088, 465,  1891, 0,    2301, 1358, 0,    2506,
    0,    1813, 1972, 0,    0,    634,  175,  2215, 1077, 0,    0,    1153, 3930, 0,    1087, 421,
    156,  303,  0,    472,  0,    1803, 92,   0,    17,   0,    1046, 1958, 0,    0,    36,   3560,
    1607, 2634, 3314, 870,  1395, 3763, 2271, 0,    252,  418,  0,    585,  3907, 0,    3401, 1562,
    1053, 0,    0,    0,    602,  0,    1077, 51,   2680, 0,    4003, 1014, 834,  0,    0,    1982,
    0,    1348, 0,    937,  1716, 88,   1548, 0,    454,  416,  0,    1115, 0,    1975, 0,    0,
    506,  3990, 0,    1185, 1594, 1308, 0,    1093, 3887, 0,    1063, 0,    0,    0,    1474, 0,
    3478, 1691, 31,   0,    1698, 0,    3826, 564,  0,    397,  2730, 0,    1553, 1720, 482,  2809,
    2158, 0,    1538, 0,    3567, 3219, 0,    1885, 3759, 1515, 1356, 176,  1411, 1942, 1331, 1296,
    2033, 246,  3492, 519,  629,  2798, 728,  529,  3872, 0,    608,  0,    12,   979,  1339, 0,
    663,  3429, 0,    3332, 0,    664,  0,    0,    1711, 0,    0,    2140, 2980, 296,  451,  606,
    1439, 925,  458,  1550, 3563, 1414, 3971, 737,  0,    561,  0,    0,    1155, 0,    1239, 0,
    1423, 1597, 2653, 0,    661,  0,    0,    535,  1442, 1648, 2281, 622,  3931, 565,  1126, 0,
    965,  806,  1069, 0,    0,    2427, 1527, 94,   660,  2027, 1565, 0,    0,    2205, 218,  0,
    755,  0,    976,  0,    1502, 1102, 0,    3575, 3832, 0,    0,    0,    1229, 2706, 3256, 0,
    0,    0,    0,    0,    888,  0,    1734, 2280, 1397, 667,  707,  0,    1166, 1809, 0,    0,
    1596, 0,    594,  1481, 0,    333,  2669, 0,    3101, 0,    748,  1657, 11,   0,    1671, 3962,
    3716, 0,    0,    40,   1031, 0,    482,  0,    0,    0,    0,    1322, 1304, 1818, 3332, 424,
    932,  205,  0,    1180, 1987, 2057, 0,    1516, 1033, 186,  1260, 3232, 876,  1011, 1469, 178,
    2960, 0,    924,  1430, 0,    0,    0,    0,    1699, 152,  163,  1168, 0,    694,  0,    0,
    1431, 0,    768,  0,    942,  1860, 0,    0,    763,  1917, 0,    1336, 0,    1264, 0,    0,
    0,    0,    0,    1067, 0,    3677, 2664, 0,    2320, 1078, 3926, 0,    0,    1301, 0,    3539,
    695,  2037, 0,    2484, 2762, 0,    2440, 249,  1053, 0,    533,  1430, 98,   3585, 2924, 1951,
    0,    1899, 3951, 0,    0,    19,   659,  3734, 1995, 579,  0,    0,    0,    1171, 3963, 0,
    796,  2749, 0,    3432, 745,  3778, 999,  0,    885,  3271, 1597, 866,  0,    3336, 1767, 0,
    0,    721,  0,    924,  3979, 1872, 0,    0,    1306, 316,  327,  1262, 0,    1232, 3989, 0,
    342,  0,    3541, 0,    3897, 0,    1360, 0,    0,    0,    2050, 383,  0,    0,    2232, 0,
    0,    182,  3383, 3882, 1563, 0,    2112, 1504, 0,    0,    0,    0,    2024, 0,    2335, 0,
    3598, 0,    1947, 1955, 1807, 1759, 2409, 3427, 265,  2115, 650,  0,    405,  1837, 1497, 2096,
    1637, 1682, 2135, 0,    0,    0,    657,  1599, 3938, 0,    0,    0,    1629, 0,    363,  3170,
    245,  974,  0,    0,    0,    1098, 3364, 1627, 2556, 2043, 2810, 0,    0,    895,  1306, 2706,
    3795, 607,  588,  2841, 1932, 3974, 3716, 0,    947,  1974, 1112, 0,    119,  0,    1174, 1925,
    2756, 3311, 0,    0,    452,  1190, 1060, 0,    0,    1701, 789,  1819, 0,    122,  0,    2125,
    1036, 1647, 0,    1260, 0,    0,    1106, 0,    3435, 0,    2707, 1391, 450,  0,    0,    0,
    830,  0,    0,    0,    0,    0,    3426, 1820, 1513, 0,    0,    2902, 0,    1132, 0,    2001,
    1700, 0,    752,  1197, 2024, 0,    0,    271,  2593, 0,    2897, 1741, 2020, 819,  3396, 0,
    0,    0,    2068, 0,    1136, 3783, 3740, 2773, 0,    1238, 356,  0,    0,    3586, 516,  985,
    0,    0,    1519, 1235, 0,    3110, 0,    116,  0,    0,    364,  153,  3938, 610,  3970, 79,
    0,    3992, 0,    0,    1082, 2122, 3106, 0,    0,    848,  2823, 0,    1745, 3310, 0,    1529,
    1314, 805,  0,    0,    269,  0,    17,   0,    1711, 0,    360,  1332, 2053, 698,  0,    796,
    2458, 0,    0,    0,    3865, 0,    3839, 2148, 966,  1206, 259,  0,    0,    0,    3866, 776,
    1995, 0,    0,    0,    297,  0,    1905, 272,  2471, 0,    111,  0,    1002, 1216, 1758, 1302,
    0,    0,    1046, 0,    2853, 0,    4015, 2345, 57,   1672, 903,  0,    3757, 135,  3985, 0,
    572,  250,  0,    1655, 3489, 1505, 1921, 1386, 0,    0,    300,  207,  685,  2059, 270,  1494,
    293,  0,    286,  0,    1527, 1351, 0,    0,    0,    3688, 909,  3387, 2672, 0,    0,    0,
    0,    1664, 3886, 3838, 2324, 0,    0,    3508, 3919, 1726, 0,    1972, 1186, 0,    105,  0,
    2686, 0,    1664, 3786, 1123, 0,    2098, 2622, 3679, 0,    387,  1595, 1026, 910,  3226, 2782,
    1455, 607,  1346, 409,  0,    1934, 0,    1174, 515,  247,  545,  1599, 0,    1748, 899,  3,
    0,    1885, 0,    2011, 3137, 408};

int MangledHashG(const char *key, const int *T)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += T[i] * key[i];
        sum %= 4022;
    }
    return mangledkG[sum];
}

int MangledPerfectHash(const char *key)
{
    if (strlen(key) > 37)
        return 0;

    return (MangledHashG(key, mangledkT1) + MangledHashG(key, mangledkT2)) % 4022;
}

constexpr int unmangledkT1[] = {144, 106, 306, 148, 131, 219, 212, 45,  287, 341, 277, 20,  111,
                                58,  208, 119, 14,  175, 302, 100, 209, 295, 267, 0,   229, 180};
constexpr int unmangledkT2[] = {121, 122, 34, 65,  319, 69,  163, 60, 246, 67,  291, 196, 119,
                                224, 117, 41, 360, 309, 210, 88,  98, 242, 241, 278, 10,  1};
constexpr int unmangledkG[]  = {
    0,   0,   0,   362, 169, 0,   214, 0,   0,   149, 0,   364, 0,   84,  271, 0,   0,   0,   0,
    26,  0,   190, 0,   0,   0,   0,   0,   84,  6,   0,   0,   47,  0,   0,   170, 0,   36,  74,
    236, 0,   83,  0,   0,   0,   65,  189, 118, 0,   0,   0,   1,   65,  245, 35,  317, 71,  326,
    0,   132, 0,   74,  0,   337, 0,   0,   76,  0,   0,   98,  0,   0,   43,  0,   40,  0,   51,
    341, 23,  0,   0,   241, 0,   0,   0,   0,   0,   186, 0,   0,   0,   102, 44,  184, 0,   0,
    351, 0,   81,  25,  104, 61,  0,   0,   118, 0,   69,  177, 0,   360, 344, 0,   0,   0,   0,
    156, 0,   41,  0,   0,   0,   0,   86,  314, 0,   14,  12,  0,   0,   0,   177, 285, 0,   0,
    119, 0,   110, 0,   0,   0,   0,   291, 0,   188, 270, 309, 357, 0,   5,   346, 129, 20,  47,
    120, 0,   151, 309, 119, 39,  167, 351, 130, 0,   51,  109, 95,  89,  171, 0,   99,  0,   168,
    67,  0,   92,  323, 13,  74,  178, 0,   248, 49,  0,   64,  186, 156, 0,   136, 300, 0,   0,
    0,   129, 19,  0,   140, 0,   0,   185, 287, 184, 0,   314, 0,   352, 63,  108, 49,  0,   277,
    0,   0,   19,  286, 202, 127, 0,   52,  288, 311, 74,  0,   0,   87,  74,  29,  121, 25,  35,
    1,   0,   0,   355, 98,  0,   93,  135, 205, 30,  30,  108, 248, 0,   0,   0,   22,  0,   24,
    2,   20,  299, 0,   0,   265, 0,   0,   0,   169, 93,  93,  15,  93,  239, 94,  6,   0,   0,
    0,   332, 284, 0,   131, 298, 2,   0,   126, 0,   0,   297, 183, 0,   0,   277, 0,   149, 162,
    133, 111, 0,   332, 246, 191, 0,   0,   15,  54,  0,   0,   37,  124, 0,   0,   0,   15,  141,
    0,   0,   0,   0,   50,  0,   0,   348, 0,   112, 0,   39,  51,  67,  259, 91,  97,  176, 31,
    0,   175, 24,  0,   156, 0,   0,   75,  107, 127, 60,  0,   106, 105, 0,   0,   59,  317, 0,
    17,  131, 0,   203, 0,   0,   0,   91,  50,  15,  62,  0,   128, 0,   0,   167, 267, 0,   261,
    200, 0,   73,  0};

int UnmangledHashG(const char *key, const int *T)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += T[i] * key[i];
        sum %= 365;
    }
    return unmangledkG[sum];
}

int UnmangledPerfectHash(const char *key)
{
    if (strlen(key) > 26)
        return 0;

    return (UnmangledHashG(key, unmangledkT1) + UnmangledHashG(key, unmangledkT2)) % 365;
}

}  // namespace

namespace sh
{

template <>
const size_t ImmutableString::FowlerNollVoHash<4>::kFnvPrime = 16777619u;

template <>
const size_t ImmutableString::FowlerNollVoHash<4>::kFnvOffsetBasis = 0x811c9dc5u;

template <>
const size_t ImmutableString::FowlerNollVoHash<8>::kFnvPrime =
    static_cast<size_t>(1099511628211ull);

template <>
const size_t ImmutableString::FowlerNollVoHash<8>::kFnvOffsetBasis =
    static_cast<size_t>(0xcbf29ce484222325ull);

uint32_t ImmutableString::mangledNameHash() const
{
    return MangledPerfectHash(data());
}

uint32_t ImmutableString::unmangledNameHash() const
{
    return UnmangledPerfectHash(data());
}

}  // namespace sh
