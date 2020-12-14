// GENERATED FILE - DO NOT EDIT.
// Generated by gen_builtin_symbols.py using data from builtin_variables.json and
// builtin_function_declarations.txt.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
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

constexpr int mangledkT1[] = {3739, 1631, 2789, 3000, 1313, 1833, 2647, 2265, 4243, 3275,
                              388,  3099, 2680, 2382, 1469, 3517, 4113, 1467, 2188, 3241,
                              3443, 3499, 3370, 4109, 1589, 936,  1009, 2094, 714,  2729,
                              1131, 512,  2199, 2280, 3218, 4074, 983,  595,  997,  3186};
constexpr int mangledkT2[] = {1278, 2599, 3960, 322,  3743, 3174, 3743, 4020, 3366, 3013,
                              428,  2584, 153,  1976, 382,  2752, 147,  3332, 3015, 381,
                              593,  4320, 2140, 2563, 411,  3650, 4300, 3733, 2052, 570,
                              3398, 1746, 2534, 14,   1119, 2620, 140,  2374, 4039, 744};
constexpr int mangledkG[]  = {
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1753, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    377,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    3702,
    0,    0,    0,    3743, 0,    1142, 4406, 0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    403,  0,    486,  0,
    0,    0,    0,    0,    0,    4057, 4358, 0,    0,    0,    2120, 0,    0,    0,    0,    0,
    0,    1158, 2155, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    542,  0,    0,    0,    469,  0,    0,    0,
    0,    0,    0,    0,    0,    841,  3728, 0,    0,    0,    3555, 0,    0,    4167, 0,    0,
    0,    0,    0,    0,    0,    0,    606,  0,    0,    3503, 1148, 0,    2175, 0,    0,    0,
    0,    4395, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    4044, 1358, 173,  0,    0,    0,    0,    0,    0,    2895, 0,    0,    37,   1119, 768,  0,
    0,    0,    3246, 0,    0,    0,    0,    3146, 164,  0,    0,    1169, 877,  1436, 0,    4032,
    919,  0,    0,    0,    0,    0,    0,    0,    286,  0,    0,    0,    0,    0,    0,    4398,
    1858, 4128, 0,    0,    0,    0,    0,    0,    4194, 0,    1143, 0,    0,    0,    580,  0,
    0,    0,    0,    0,    0,    3421, 0,    0,    0,    0,    0,    0,    130,  1535, 3354, 0,
    0,    0,    0,    0,    0,    0,    1738, 0,    3458, 0,    0,    0,    1370, 0,    2618, 0,
    1315, 269,  0,    0,    0,    4394, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    4021, 0,    0,    0,    1722, 0,    2988, 0,    4339, 0,    0,    1113, 0,    0,    0,    0,
    0,    0,    2554, 0,    0,    4468, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3714, 1688, 0,    0,    3841, 3690, 0,    0,    0,    1154, 0,    0,    0,    0,    0,
    0,    0,    2734, 0,    368,  1579, 0,    174,  0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    1085, 186,  0,    0,    0,    0,    0,    0,    0,    662,  0,    0,    0,
    0,    600,  2260, 0,    640,  0,    0,    0,    0,    0,    0,    0,    2698, 0,    0,    0,
    0,    4327, 0,    0,    0,    0,    0,    0,    0,    207,  0,    4125, 0,    0,    0,    2080,
    0,    0,    2581, 1845, 0,    817,  2195, 0,    0,    2013, 0,    0,    0,    3529, 0,    0,
    0,    0,    0,    0,    726,  647,  0,    2765, 1247, 0,    0,    3232, 0,    0,    0,    0,
    0,    0,    0,    0,    0,    3289, 0,    0,    4236, 0,    0,    0,    0,    0,    0,    0,
    0,    0,    843,  0,    0,    0,    0,    0,    0,    652,  0,    0,    1669, 0,    0,    370,
    4237, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    4517, 2240,
    0,    0,    0,    0,    0,    0,    0,    740,  0,    2759, 3799, 4366, 0,    0,    0,    0,
    0,    0,    0,    3912, 479,  0,    0,    0,    0,    0,    4518, 0,    0,    0,    2717, 0,
    692,  0,    0,    0,    570,  0,    3639, 0,    0,    3926, 0,    0,    0,    0,    0,    0,
    2397, 1547, 1232, 0,    0,    2937, 1518, 0,    0,    0,    1222, 0,    2813, 0,    0,    2324,
    0,    0,    0,    0,    0,    0,    0,    860,  0,    3950, 0,    0,    2826, 0,    0,    0,
    0,    0,    0,    925,  0,    0,    0,    1598, 0,    0,    0,    0,    227,  0,    0,    0,
    0,    3468, 0,    0,    0,    0,    120,  1162, 2435, 387,  0,    0,    0,    0,    0,    0,
    0,    308,  0,    0,    0,    0,    0,    2650, 0,    0,    3881, 0,    4091, 0,    0,    501,
    0,    0,    3368, 0,    0,    0,    4093, 0,    0,    0,    0,    0,    0,    934,  0,    0,
    0,    0,    2157, 0,    1082, 0,    0,    0,    1021, 3875, 0,    253,  0,    0,    140,  0,
    0,    1903, 0,    0,    0,    0,    2137, 1473, 0,    0,    461,  0,    0,    0,    3575, 0,
    0,    958,  0,    0,    789,  0,    0,    3195, 0,    0,    0,    3853, 0,    2074, 0,    0,
    0,    1681, 0,    0,    0,    1623, 982,  0,    0,    4204, 0,    0,    0,    0,    0,    0,
    926,  4075, 1657, 0,    0,    1534, 0,    0,    742,  3347, 0,    2568, 0,    0,    0,    0,
    3836, 0,    718,  3974, 3474, 0,    3682, 3367, 1057, 0,    0,    0,    0,    0,    567,  0,
    0,    753,  0,    1333, 0,    0,    4057, 0,    0,    0,    0,    291,  4398, 0,    0,    3324,
    1344, 0,    0,    0,    1107, 0,    0,    0,    3756, 2315, 3176, 2972, 0,    0,    0,    0,
    0,    1958, 1448, 0,    2941, 2,    0,    225,  3233, 0,    2946, 0,    3610, 0,    876,  0,
    0,    0,    3606, 1662, 0,    0,    4469, 1999, 3846, 942,  0,    0,    0,    2089, 2152, 0,
    0,    0,    0,    1508, 0,    491,  633,  868,  0,    0,    36,   0,    0,    1767, 0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    278,  212,  0,    0,    0,    0,    0,    0,
    956,  2657, 0,    2192, 0,    1829, 2305, 0,    0,    0,    0,    0,    0,    0,    3393, 4016,
    0,    0,    0,    0,    2033, 0,    0,    0,    0,    0,    543,  0,    0,    1619, 1394, 4136,
    0,    0,    0,    0,    1263, 0,    3559, 0,    0,    0,    1735, 3421, 0,    3999, 351,  791,
    0,    0,    0,    0,    2988, 0,    49,   647,  1231, 2090, 338,  86,   0,    0,    4294, 0,
    0,    0,    0,    0,    0,    317,  1168, 0,    1066, 0,    0,    0,    0,    726,  0,    0,
    1147, 0,    0,    0,    84,   0,    0,    0,    1282, 0,    561,  0,    4462, 1699, 454,  0,
    0,    0,    655,  0,    1560, 0,    0,    667,  0,    0,    118,  0,    1064, 509,  0,    0,
    0,    0,    0,    0,    0,    0,    496,  0,    212,  0,    0,    0,    0,    0,    0,    0,
    0,    0,    4222, 3978, 0,    0,    0,    0,    0,    0,    1783, 2735, 2714, 2018, 0,    0,
    2421, 0,    0,    0,    0,    2271, 0,    3422, 1929, 0,    0,    714,  4436, 0,    0,    0,
    2156, 0,    0,    2137, 0,    0,    1113, 0,    0,    4107, 0,    4353, 0,    0,    0,    0,
    655,  0,    0,    1111, 1404, 0,    1641, 3411, 2047, 0,    0,    0,    0,    0,    0,    2521,
    3273, 0,    0,    0,    0,    0,    0,    0,    0,    333,  401,  0,    0,    0,    0,    4406,
    0,    0,    1119, 1739, 0,    0,    1880, 0,    130,  3433, 222,  4450, 0,    0,    3128, 201,
    0,    0,    0,    0,    3749, 3181, 0,    3831, 0,    2766, 0,    0,    0,    679,  0,    393,
    0,    0,    1739, 2450, 302,  1684, 417,  0,    0,    0,    30,   3334, 0,    1632, 0,    0,
    948,  0,    4211, 2980, 2106, 0,    0,    0,    1766, 767,  0,    0,    2707, 0,    978,  4412,
    0,    0,    4448, 0,    449,  1451, 4348, 0,    2607, 0,    0,    299,  0,    0,    209,  3891,
    0,    1770, 574,  0,    1465, 0,    269,  2301, 520,  0,    0,    0,    1543, 1322, 0,    0,
    4263, 0,    0,    2241, 0,    0,    301,  0,    0,    3587, 0,    0,    0,    1319, 3975, 813,
    0,    0,    0,    924,  0,    0,    938,  0,    0,    0,    0,    0,    0,    0,    2307, 0,
    0,    1403, 109,  988,  0,    0,    0,    0,    1179, 360,  2074, 0,    0,    0,    0,    0,
    3246, 0,    265,  500,  0,    473,  3206, 0,    0,    124,  888,  969,  0,    0,    0,    2,
    60,   2347, 4193, 0,    0,    3285, 0,    0,    1758, 0,    57,   1641, 1609, 325,  2401, 0,
    1970, 4444, 219,  0,    0,    0,    0,    4160, 0,    0,    0,    0,    0,    0,    0,    2540,
    0,    0,    0,    0,    0,    1071, 0,    0,    0,    0,    1461, 0,    0,    0,    0,    0,
    0,    1085, 0,    0,    3778, 1332, 636,  291,  0,    0,    2220, 0,    442,  0,    0,    0,
    0,    1821, 0,    3654, 0,    635,  0,    0,    0,    269,  0,    0,    2333, 0,    1109, 0,
    0,    0,    1784, 0,    4306, 0,    0,    0,    861,  0,    1790, 2994, 0,    980,  0,    0,
    0,    1822, 4093, 3881, 0,    2709, 0,    0,    1908, 0,    0,    0,    0,    3265, 1149, 4035,
    0,    0,    3350, 1698, 1154, 1957, 0,    0,    0,    0,    0,    0,    0,    3686, 3238, 0,
    0,    0,    0,    1528, 0,    1609, 0,    1494, 1785, 211,  1055, 0,    0,    0,    4499, 0,
    0,    0,    0,    0,    0,    0,    0,    1251, 2175, 0,    0,    389,  0,    2192, 0,    0,
    0,    3467, 417,  0,    0,    1849, 1236, 1106, 0,    114,  2144, 1691, 2776, 0,    1190, 0,
    523,  0,    0,    266,  2414, 4448, 3858, 0,    0,    0,    1116, 3321, 0,    0,    4208, 0,
    609,  0,    3862, 2016, 0,    0,    737,  1214, 4516, 505,  0,    1725, 0,    0,    2011, 1777,
    0,    0,    0,    4180, 1709, 0,    3182, 0,    883,  0,    0,    0,    0,    0,    0,    1121,
    0,    0,    0,    0,    0,    937,  0,    3880, 1125, 1355, 0,    788,  282,  0,    1575, 155,
    0,    1732, 0,    0,    0,    4047, 1410, 1406, 0,    2013, 0,    0,    471,  176,  0,    0,
    0,    3570, 0,    973,  1005, 0,    0,    0,    0,    895,  0,    626,  979,  0,    977,  0,
    0,    663,  4079, 721,  0,    0,    0,    4111, 337,  615,  0,    137,  215,  0,    527,  0,
    0,    0,    0,    4450, 0,    0,    2050, 21,   573,  0,    0,    0,    0,    0,    0,    2452,
    0,    0,    0,    0,    956,  0,    0,    0,    0,    556,  0,    0,    1261, 360,  0,    4177,
    0,    0,    727,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    4336, 1792,
    211,  0,    1706, 0,    0,    0,    0,    0,    0,    2432, 0,    4044, 701,  374,  1991, 3954,
    4020, 238,  712,  0,    857,  999,  2016, 1290, 0,    431,  1471, 0,    0,    0,    0,    2106,
    460,  0,    0,    1951, 1017, 0,    459,  0,    652,  0,    349,  0,    246,  0,    178,  0,
    1351, 1325, 0,    0,    0,    0,    0,    0,    0,    0,    163,  0,    3395, 0,    303,  3838,
    0,    241,  0,    4274, 0,    2112, 2001, 0,    709,  493,  0,    0,    3640, 0,    1810, 0,
    1584, 3635, 0,    0,    1195, 752,  2363, 0,    0,    0,    0,    0,    1061, 1389, 0,    555,
    983,  326,  1546, 1521, 0,    0,    838,  676,  0,    0,    328,  2301, 4134, 4032, 0,    3019,
    0,    982,  0,    0,    774,  2899, 0,    0,    0,    147,  26,   3651, 2118, 702,  0,    2382,
    1146, 608,  194,  0,    2058, 0,    0,    1630, 0,    0,    0,    0,    0,    507,  0,    618,
    807,  340,  0,    0,    1152, 0,    0,    0,    1838, 1022, 0,    4463, 531,  0,    0,    377,
    787,  1053, 864,  3486, 16,   0,    0,    2133, 0,    0,    223,  0,    3898, 0,    0,    3865,
    0,    0,    0,    213,  0,    0,    0,    0,    1207, 1100, 0,    0,    0,    1884, 0,    1898,
    423,  1197, 3896, 535,  0,    582,  662,  0,    2310, 310,  0,    2709, 4489, 884,  1993, 68,
    3161, 626,  0,    0,    0,    0,    0,    4078, 755,  164,  247,  0,    1210, 0,    1484, 279,
    0,    573,  0,    0,    0,    1441, 3329, 2467, 1563, 0,    0,    0,    3011, 676,  1354, 0,
    0,    4380, 1935, 3695, 0,    967,  0,    632,  1353, 2014, 3712, 1407, 1087, 0,    4228, 0,
    4185, 0,    0,    1429, 1735, 1634, 1947, 0,    0,    1585, 0,    0,    0,    2581, 1971, 0,
    2909, 0,    0,    0,    505,  0,    0,    0,    0,    2876, 776,  0,    0,    4053, 0,    0,
    541,  0,    0,    1614, 2525, 4049, 3871, 1797, 244,  549,  0,    3490, 2532, 287,  0,    0,
    1555, 0,    0,    1125, 1717, 3731, 4240, 50,   1164, 761,  0,    2149, 0,    1401, 0,    1333,
    3242, 0,    2049, 1773, 0,    0,    0,    4386, 0,    1811, 0,    951,  0,    483,  0,    3682,
    0,    1297, 991,  0,    229,  0,    3210, 1442, 2939, 1895, 3431, 0,    213,  855,  346,  681,
    0,    2025, 0,    0,    0,    0,    0,    0,    2007, 4242, 0,    1045, 35,   0,    0,    0,
    0,    0,    1905, 0,    3035, 0,    0,    0,    893,  3851, 0,    0,    0,    0,    3374, 38,
    0,    0,    1204, 0,    768,  0,    0,    0,    1134, 0,    0,    0,    0,    4315, 385,  1727,
    2540, 4128, 0,    3121, 0,    0,    0,    0,    0,    4163, 1475, 0,    1629, 1496, 0,    0,
    985,  0,    0,    322,  0,    0,    2100, 0,    125,  0,    4466, 2035, 0,    0,    314,  1737,
    3186, 0,    21,   1472, 0,    0,    4448, 4158, 378,  2124, 0,    1020, 863,  485,  0,    4223,
    0,    392,  0,    0,    0,    2440, 259,  0,    0,    0,    3445, 0,    615,  0,    0,    3693,
    1376, 0,    0,    203,  3723, 990,  1340, 332,  0,    0,    1289, 1313, 0,    2041, 0,    0,
    1085, 2095, 268,  786,  2146, 0,    0,    0,    2547, 0,    0,    0,    1956, 4320, 0,    0,
    0,    113,  0,    625,  0,    1052, 800,  4425, 2077, 0,    0,    881,  0,    0,    817,  537,
    3707, 0,    1539, 0,    0,    0,    0,    0,    0,    728,  0,    48,   519,  0,    0,    874,
    0,    0,    0,    3739, 1225, 0,    0,    1063, 274,  3763, 762,  0,    3159, 0,    1176, 0,
    1479, 324,  0,    1200, 0,    0,    0,    395,  0,    0,    4339, 0,    0,    518,  3197, 0,
    753,  676,  2199, 0,    278,  2788, 2215, 0,    1975, 1514, 17,   0,    0,    0,    0,    673,
    932,  115,  0,    4379, 1702, 95,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    972,  0,    1930, 1765, 0,    1923, 1036, 0,    4471, 0,    1491, 0,    0,    366,  0,    0,
    0,    4238, 1037, 0,    1760, 1693, 0,    0,    0,    4173, 256,  669,  0,    0,    3634, 28,
    0,    0,    0,    0,    0,    0,    0,    314,  936,  2871, 0,    450,  0,    2942, 1205, 44,
    3355, 1380, 230,  1159, 0,    0,    4014, 0,    0,    0,    0,    1196, 2832, 0,    0,    0,
    687,  0,    0,    0,    1043, 0,    0,    0,    4384, 752,  3135, 1242, 440,  1315, 0,    0,
    3204, 0,    0,    1645, 0,    0,    1180, 0,    0,    0,    0,    0,    1216, 0,    0,    1005,
    4204, 0,    0,    0,    0,    0,    0,    2484, 0,    3993, 0,    0,    4342, 0,    2982, 0,
    1078, 0,    0,    3889, 1175, 0,    0,    0,    1389, 0,    0,    0,    232,  2134, 0,    0,
    4295, 479,  3904, 0,    0,    1523, 328,  0,    0,    3944, 0,    0,    112,  636,  0,    3330,
    1169, 0,    0,    0,    3743, 3225, 0,    0,    0,    217,  0,    0,    0,    0,    3762, 0,
    47,   3469, 0,    1150, 1171, 0,    647,  750,  0,    3637, 2123, 2973, 3383, 126,  0,    977,
    0,    0,    0,    1542, 0,    0,    0,    1549, 1024, 1239, 2979, 1147, 0,    75,   1697, 0,
    0,    0,    0,    0,    1523, 1058, 0,    285,  3098, 0,    0,    1907, 1206, 0,    2131, 1782,
    176,  1977, 1748, 1591, 0,    0,    0,    810,  172,  704,  1220, 96,   0,    4073, 435,  0,
    0,    1841, 472,  2086, 0,    637,  2857, 149,  3505, 0,    4124, 0,    1862, 242,  2002, 2175,
    1872, 0,    0,    199,  0,    2119, 0,    0,    2060, 3079, 4300, 0,    0,    773,  724,  0,
    222,  0,    2314, 680,  0,    3165, 0,    0,    3920, 0,    0,    0,    729,  229,  313,  0,
    0,    4205, 2248, 4500, 0,    0,    0,    14,   2992, 671,  0,    0,    0,    1762, 1994, 674,
    1161, 2142, 4087, 1829, 425,  0,    495,  0,    2403, 0,    0,    946,  0,    0,    0,    0,
    1433, 913,  0,    1263, 1985, 325,  0,    0,    2121, 0,    162,  0,    1945, 0,    2119, 0,
    772,  1957, 0,    0,    0,    0,    1069, 0,    4320, 4413, 0,    0,    2423, 0,    0,    0,
    2748, 964,  3686, 0,    2746, 0,    0,    0,    0,    0,    3144, 1396, 940,  533,  1670, 0,
    0,    4025, 0,    1323, 100,  0,    1712, 0,    3711, 383,  0,    0,    3705, 860,  0,    0,
    2331, 1393, 513,  3693, 1964, 1412, 1561, 4360, 1252, 2113, 0,    3658, 0,    2093, 2868, 0,
    646,  771,  0,    0,    1452, 0,    4331, 0,    2091, 4103, 0,    0,    0,    3661, 1968, 1897,
    3052, 3582, 2843, 0,    0,    0,    0,    0,    197,  0,    0,    0,    0,    0,    0,    3747,
    471,  0,    0,    0,    3159, 1740, 605,  0,    2316, 0,    0,    3725, 0,    1996, 0,    0,
    4289, 306,  0,    0,    1880, 0,    0,    4253, 0,    0,    1416, 716,  1067, 364,  1184, 0,
    0,    901,  0,    0,    0,    0,    1502, 0,    0,    398,  1346, 3817, 0,    778,  861,  0,
    3471, 0,    0,    3181, 0,    0,    0,    0,    0,    0,    1947, 0,    0,    427,  0,    1079,
    0,    2736, 1189, 2165, 941,  4424, 0,    1307, 0,    0,    965,  186,  2409, 0,    0,    1755,
    0,    884,  4334, 0,    0,    0,    465,  0,    2370, 0,    10,   0,    749,  0,    2695, 0,
    0,    1203, 0,    0,    1469, 2493, 0,    0,    1105, 0,    0,    0,    616,  2795, 0,    0,
    1614, 0,    1339, 0,    0,    1963, 2242, 1841, 151,  709,  0,    1196, 0,    0,    0,    1293,
    110,  1404, 245,  0,    0,    913,  0,    0,    228,  1563, 402,  0,    0,    2028, 0,    107,
    3387, 3070, 2015, 0,    1205, 0,    0,    3529, 4006, 1831, 806,  4448, 1900, 38,   820,  1450,
    0,    0,    1237, 1232, 4492, 291,  1687, 143,  725,  665,  2097, 0,    0,    375,  0,    0,
    0,    1742, 0,    0,    1430, 0,    739,  986,  1342, 0,    1145, 1199, 0,    1992, 2003, 635,
    0,    4368, 0,    0,    0,    0,    412,  4306, 3152, 2125, 0,    3107, 0,    4240, 0,    0,
    3046, 727,  0,    3965, 1517, 0,    3173, 0,    0,    4096, 0,    0,    0,    0,    0,    0,
    1151, 530,  0,    0,    0,    474,  1267, 316,  2360, 4362, 992,  2209, 0,    0,    0,    0,
    2374, 699,  540,  800,  1861, 1078, 0,    2108, 2536, 0,    713,  323,  0,    273,  0,    0,
    355,  1817, 395,  0,    1508, 3151, 0,    2149, 4020, 0,    0,    372,  0,    0,    1137, 0,
    1351, 0,    0,    3212, 0,    0,    599,  0,    1852, 1899, 947,  0,    970,  0,    0,    0,
    766,  950,  829,  419,  784,  0,    0,    225,  0,    1300, 179,  0,    85,   3598, 2487, 3185,
    0,    3289, 2580, 0,    1503, 1717, 177,  0,    2099, 294,  1226, 0,    2065, 3896, 0,    0,
    3322, 1376, 3816, 4013, 4114, 917,  0,    3833, 0,    1692, 0,    477,  0,    0,    0,    71,
    0,    0,    0,    1156, 0,    1081, 4369, 0,    0,    1111, 2971, 0,    0,    0,    3585, 325,
    0,    1278, 0,    0,    129,  676,  0,    0,    2629, 2583, 489,  491,  613,  2031, 0,    1211,
    0,    0,    1029, 271,  0,    0,    1203, 3794, 0,    4246, 0,    0,    2074, 3293, 1014, 4484,
    0,    0,    0,    3124, 0,    0,    0,    0,    269,  0,    549,  0,    1984, 0,    0,    2529,
    0,    0,    614,  1175, 1915, 0,    0,    0,    885,  2791, 1914, 484,  4352, 1605, 4239, 0,
    0,    681,  896,  3954, 867,  156,  327,  2955, 0,    3523, 0,    1467, 689,  0,    0,    0,
    635,  961,  0,    572,  0,    2331, 1526, 519,  1286, 0,    1865, 1864, 1651, 1304, 0,    4352,
    692,  0,    1476, 0,    0,    4112, 0,    692,  131,  2253, 1686, 143,  0,    4083, 1779, 0,
    0,    670,  0,    915,  1019, 0,    4444, 718,  1674, 1968, 0,    1035, 652,  1127, 2903, 0,
    1683, 0,    472,  4195, 4238, 0,    0,    2141, 3516, 0,    3348, 0,    0,    23,   372,  1138,
    0,    0,    29,   1701, 0,    3048, 1892, 0,    0,    4071, 1390, 0,    98,   0,    1377, 0,
    0,    0,    1715, 3063, 1441, 208,  0,    734,  1338, 0,    641,  4487, 0,    0,    0,    702,
    2682, 0,    4442, 0,    1965, 1616, 0,    1024, 1628, 1662, 0,    1091, 2311, 0,    0,    422,
    0,    333,  0,    1889, 0,    0,    0,    0,    0,    4497, 0,    0,    2655, 3474, 1316, 123,
    1851, 3755, 3915, 0,    0,    0,    356,  1124, 325,  77,   0,    0,    3,    0,    0,    80,
    1885, 0,    1638, 0,    0,    0,    3601, 2497, 1509, 0,    0,    0,    3401, 0,    0,    0,
    2679, 0,    2071, 1113, 0,    0,    3696, 0,    642,  0,    0,    1215, 1392, 2018, 3821, 12,
    1051, 2726, 677,  4340, 519,  1973, 2742, 820,  0,    0,    343,  191,  1390, 0,    0,    544,
    0,    4177, 4130, 70,   40,   1671, 0,    0,    1609, 366,  945,  0,    0,    3904, 7,    0,
    1974, 0,    0,    0,    3737, 1275, 0,    2572, 0,    2004, 0,    1502, 3277, 1408, 2631, 1647,
    2097, 970,  533,  0,    0,    0,    859,  1729, 705,  4030, 678,  1255, 0,    1015, 2392, 1084,
    1942, 0,    3962, 1676, 0,    2401, 4236, 0,    1342, 932,  0,    0,    224,  626,  837,  0,
    4235, 0,    1045, 0,    0,    0,    0,    2050, 389,  0,    63,   4431, 0,    671,  0,    0,
    1001, 0,    546,  4294, 132,  266,  2080, 1421, 0,    4103, 0,    9,    3595, 4457, 4036, 0,
    4363, 0,    77,   1380, 1354, 1642, 1112, 3747, 3346, 3697, 1455, 0,    1036, 2278, 526,  0,
    1815, 1725, 808,  562,  0,    0,    4484, 0,    0,    572,  0,    1920, 0,    0,    0,    0,
    945,  0,    0,    1157, 84,   1033, 0,    320,  0,    2610, 0,    1716, 0,    4409, 0,    497,
    1704, 0,    2874, 0,    0,    4379, 0,    0,    0,    0,    3601, 2325, 567,  2216, 0,    0,
    0,    404,  630,  0,    2154, 2165, 649,  1156, 0,    0,    1375, 0,    2396, 474,  0,    447,
    0,    0,    734,  1511, 0,    0,    2640, 31,   0,    3815, 2055, 0,    1324, 1010, 0,    0,
    731,  1418, 0,    917,  747,  3421, 260,  0,    819,  0,    913,  1164, 3921, 0,    0,    0,
    1768, 2499, 2993, 1828, 0,    0,    0,    1078, 801,  3223, 0,    0,    1567, 0,    1602, 1074,
    0,    1798, 0,    1675, 0,    922,  4438, 1238, 1099, 0,    0,    0,    1212, 0,    0,    4498,
    4474, 0,    0,    0,    0,    127,  1732, 4295, 0,    4389, 2062, 882,  0,    0,    0,    0,
    4388, 594,  0,    983,  1738, 0,    1550, 2284, 973,  1297, 0,    2360, 0,    0,    0,    629,
    974,  0,    2813, 483,  3879, 1311, 252,  3334, 3923, 0,    0,    0,    0,    0,    89,   0,
    0,    390,  0,    1728, 0,    0,    81,   0,    1509, 1582, 0,    4111, 589,  0,    0,    699,
    1836, 1006, 0,    0,    3364, 863,  838,  0,    1047, 0,    2427, 0,    0,    0,    0,    1871,
    882,  0,    0,    4322, 0,    1216, 1522, 1237, 0,    0,    0,    0,    2351, 0,    0,    15,
    1280, 1182, 0,    4414, 2595, 853,  2089, 415,  0,    2713, 2045, 0,    2842, 0,    1280, 904,
    287,  0,    0,    0,    1316, 0,    0,    0,    0,    80,   0,    3283, 0,    0,    0,    0,
    0,    939,  0,    0,    4114, 72,   2954, 152,  1248, 0,    172,  0,    0,    0,    0,    42,
    0,    0,    0,    0,    66,   1906, 3199, 200,  0,    0,    0,    507,  1222, 666,  1557, 4127,
    0,    3052, 0,    3079, 0,    0,    4484, 313,  955,  1252, 3818, 1452, 3742, 2990, 4194, 3515,
    0,    0,    0,    1929, 1172, 3894, 38,   0,    817,  0,    1486, 1653, 1118, 3736, 668,  991,
    0,    341,  1721, 0,    902,  0,    0,    340,  0,    0,    3725, 25,   0,    0,    0,    3197,
    0,    0,    0,    0,    3530, 0,    0,    361,  0,    293,  1055, 4471, 0,    1263, 1416, 5,
    1898, 0,    186,  1187, 545,  0,    0,    0,    3627, 0,    0,    0,    121,  4013, 0,    2877,
    0,    0,    61,   2722, 3121, 0,    0,    427,  0,    0,    3172, 1767, 2900, 0,    1894, 3877,
    2537, 0,    0,    965,  1592, 3240, 336,  2650, 0,    779,  0,    1133, 0,    3582, 937,  443,
    447,  0,    2169, 0,    1258, 1989, 1008, 420,  3077, 768,  0,    0,    949,  0,    2027, 0,
    1499, 0,    0,    1698, 1863, 0,    0,    477,  2307, 2147, 3657, 755,  3798, 0,    0,    318,
    0,    307,  0,    0,    0,    2790, 0,    1532, 781,  3186, 954,  608,  3536, 2017, 0,    0,
    1311, 3452, 1918, 2456, 3876, 0,    2298, 758,  0,    0,    856,  0,    0,    2898, 373,  3964,
    750,  0,    1002, 126,  428,  1503, 0,    0,    862,  2059, 1484, 1419, 0,    0,    341,  0,
    0,    0,    267,  0,    82,   4482, 58,   4435, 0,    0,    2588, 4297, 1434, 2456, 0,    806,
    3847, 927,  459,  1877, 0,    4002, 4450, 1890, 0,    4120, 307,  0,    0,    1253, 0,    3792,
    0,    1825, 0,    0,    4230, 825,  458,  0,    0,    0,    1358, 1363, 2875, 0,    0,    2102,
    2662, 2342, 0,    0,    154,  1024, 415,  0,    3993, 0,    0,    2104, 1156, 2947, 0,    0,
    1992, 158,  529,  1286, 277,  1585, 586,  0,    0,    0,    100,  0,    3378, 3339, 4468, 0,
    1330, 1103, 0,    3326, 1959, 0,    0,    0,    0,    1114, 0,    3779, 1334, 0,    0,    0,
    90,   0,    344,  0,    903,  3245, 1023, 0,    0,    0,    277,  2147, 0,    283,  1993, 561,
    936,  0,    870,  646,  3981, 0,    3978, 0,    0,    1640, 904,  0,    0,    69,   2095, 0,
    956,  4499, 719,  0,    0,    0,    0,    4126, 1760, 746,  0,    352,  3597, 0,    697,  1639,
    453,  0,    0,    3780, 0,    208,  3222, 206,  0,    0,    839,  0,    1931, 367,  0,    1978,
    0,    0,    0,    0,    3293, 1666, 3487, 4043, 0,    729,  4367, 0,    0,    221,  3711, 355,
    0,    270,  1213, 526,  1594, 654,  0,    0,    0,    1386, 416,  0,    1279, 0,    2128, 1167,
    3109, 1711, 0,    0,    1806, 555,  1541, 1646, 0,    1472, 65,   0,    1266, 1315, 0,    4001,
    4177, 152,  2030, 1277, 3220, 1558, 578,  3055, 0,    1393, 987,  1493, 2001, 0,    0,    360,
    0,    0,    0,    0,    0,    35,   1626, 3769, 0,    3872, 0,    1177, 790,  1999, 849,  4122,
    0,    0,    0,    0,    2280, 0,    0,    1590, 0,    0,    595,  541,  804,  1432, 250,  0,
    1649, 1638, 1917, 1250, 148,  4278, 0,    505,  56,   989,  0,    0,    1254, 4158, 0,    4079,
    0,    0,    0,    0,    155,  2082, 0,    0,    1382, 688,  556,  3656, 1721, 0,    0,    718,
    0,    1369, 0,    0,    566,  4358, 1749, 0,    0,    0,    374,  1218, 1323, 0,    0,    3482,
    618,  4380, 1191, 1843, 0,    2269, 84,   548,  1337, 0,    554,  4152, 0,    1642, 2582, 3857,
    3875, 0,    0,    3980, 1244, 459,  0,    0,    486,  3379, 0,    727,  0,    3783, 438,  0,
    0,    0,    0,    0,    430,  0,    0,    2406, 575,  595,  0,    329,  765,  2193, 0,    3032,
    2704, 0,    1001, 275,  0,    668,  52,   1108, 1125, 862,  0,    2177, 0,    413,  550,  3915,
    0,    3168, 4220, 0,    0,    0,    24,   3699, 171,  0,    1772, 1512, 0,    0,    4276, 0,
    894,  0,    0,    2072, 908,  0,    0,    0,    557,  3741, 0,    1648, 0,    680,  1888, 0,
    872,  496,  2178, 0,    4518, 0,    623,  1117, 0,    0,    0,    292,  1850, 3090, 0,    0,
    0,    1728, 3042, 878,  0,    0,    4241, 3643, 0,    2085, 0,    1173, 81,   2906, 1258, 1777,
    0,    0,    1265, 933,  0,    0,    0,    0,    0,    0,    203,  3989, 0,    448,  0,    3851,
    0,    1272, 0,    4513, 4512, 1209, 0,    0,    1073, 2174, 0,    925,  0,    3377, 2781, 0,
    0,    1800, 1375, 549,  0,    0,    0,    0,    0,    0,    2073, 2199, 615,  646,  0,    1291,
    1724, 0,    1800, 2094, 1176, 1423, 1546, 847,  0,    3215, 659,  165,  1385, 1753, 0,    495,
    0,    3581, 2303, 457,  2293, 1717, 0,    4458, 0,    0,    1126, 845,  0,    0,    921,  0,
    4274, 0,    2425, 0,    122,  1469, 854,  0,    2114, 1766, 0,    0,    284,  283,  2520, 546,
    0,    0,    1334, 1879, 868,  2167, 1732, 251,  0,    2065, 1453, 4387, 0,    1121, 1570, 4147,
    0,    0,    639,  1596, 0,    0,    0,    1620, 1011, 487,  0,    0,    831,  1070, 1580, 4238,
    1540, 0,    606,  115,  0,    2423, 1617, 1503, 1486, 3554, 0,    0,    3090, 0,    1857, 0,
    981,  54,   835,  0,    0,    1446, 1357, 1470, 0,    1063, 955,  4161, 698,  0,    710,  0,
    2031, 0,    0,    3897, 1095, 1852, 0,    0,    0,    2204, 873,  953,  59,   0,    3223, 2252,
    159,  246,  0,    89,   1139, 1544, 0,    4457, 2189, 896,  438,  196,  314,  0,    842,  0,
    3681, 0,    1705, 0,    4349, 1492, 6,    3426, 879,  0,    93,   0,    0,    0,    0,    0,
    590,  0,    0,    0,    2105, 3552, 0,    4018, 2356, 601,  0,    0,    950,  498,  507,  4086,
    0,    0,    0,    0,    2045, 0,    1909, 576,  1428, 1660, 0,    0,    3853, 3807, 0,    3060,
    0,    3651, 0,    0,    259,  124,  0,    0,    3273, 1935, 0,    267,  4274, 68,   4185, 0,
    0,    885,  0,    0,    1712, 0,    0,    1538, 914,  0,    0,    0,    76,   1796, 61,   2771,
    0,    4459, 813,  0,    2039, 4408, 1331, 0,    462,  0,    104,  0,    1950, 1736, 1621, 2281,
    0,    2372, 0,    3945, 1440, 2015, 1654, 606,  0,    1611, 434,  147,  4516, 0,    1752, 2163,
    0,    1822, 2729, 1689, 737,  0,    37,   820,  408,  0,    4066, 188,  0,    918,  1445, 478,
    33,   3353, 0,    2009, 0,    0,    1058, 0,    1466, 3964, 1282, 3105, 0,    0,    4133, 3400,
    1230, 4261, 0,    0,    1318, 0,    411,  0,    2167, 0,    361,  2341, 1814};

int MangledHashG(const char *key, const int *T)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += T[i] * key[i];
        sum %= 4525;
    }
    return mangledkG[sum];
}

int MangledPerfectHash(const char *key)
{
    if (strlen(key) > 40)
        return 0;

    return (MangledHashG(key, mangledkT1) + MangledHashG(key, mangledkT2)) % 4525;
}

constexpr int unmangledkT1[] = {302, 379, 163, 169, 248, 282, 8,   197, 129, 5,   332, 34,  237,
                                115, 333, 239, 99,  112, 161, 336, 130, 94,  170, 40,  318, 26};
constexpr int unmangledkT2[] = {168, 245, 303, 8,  51,  374, 166, 1,   422, 347, 141, 33,  240,
                                11,  188, 22,  20, 172, 272, 197, 205, 284, 310, 24,  358, 97};
constexpr int unmangledkG[]  = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   106, 0,   20,  0,   0,   0,   0,   0,   50,  415, 0,   0,   0,   71,  0,   0,   0,   138,
    0,   0,   0,   339, 0,   32,  0,   0,   0,   177, 1,   147, 0,   0,   0,   110, 0,   403, 112,
    158, 0,   422, 0,   0,   0,   0,   166, 267, 105, 93,  0,   214, 362, 0,   133, 113, 0,   0,
    0,   320, 27,  0,   126, 0,   44,  79,  311, 78,  0,   0,   72,  0,   0,   0,   0,   0,   137,
    0,   238, 0,   0,   0,   0,   0,   0,   166, 142, 0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   297, 0,   0,   0,   73,  23,  256, 372, 77,  0,   0,   123, 196, 136, 0,   0,   347, 64,
    0,   60,  0,   101, 40,  0,   310, 411, 140, 0,   0,   0,   41,  0,   0,   0,   0,   177, 311,
    80,  144, 0,   198, 0,   0,   0,   149, 84,  0,   0,   0,   122, 88,  0,   354, 0,   81,  80,
    0,   100, 0,   156, 0,   0,   0,   276, 0,   107, 0,   0,   154, 0,   0,   0,   34,  368, 0,
    375, 0,   0,   330, 166, 0,   191, 34,  89,  0,   144, 0,   160, 0,   0,   220, 39,  0,   111,
    8,   28,  0,   18,  62,  138, 115, 0,   26,  27,  3,   4,   142, 13,  47,  127, 0,   209, 163,
    318, 0,   0,   17,  381, 0,   124, 0,   10,  0,   0,   156, 0,   0,   11,  316, 79,  0,   0,
    110, 0,   0,   330, 0,   13,  35,  0,   0,   24,  8,   138, 1,   387, 23,  202, 0,   0,   27,
    109, 11,  0,   174, 26,  291, 0,   0,   42,  197, 14,  134, 0,   94,  0,   0,   4,   0,   106,
    159, 292, 0,   49,  0,   347, 0,   62,  384, 131, 29,  0,   0,   153, 0,   164, 0,   172, 0,
    197, 0,   361, 0,   0,   7,   0,   0,   0,   311, 275, 212, 9,   118, 0,   0,   0,   42,  35,
    0,   0,   46,  116, 413, 398, 123, 229, 42,  0,   0,   200, 0,   142, 0,   296, 51,  0,   0,
    85,  341, 413, 0,   0,   0,   377, 0,   0,   0,   0,   24,  95,  183, 53,  18,  325, 0,   7,
    23,  202, 0,   0,   3,   387, 128, 0,   146, 63,  382, 0,   0,   0,   0,   0,   165, 0,   322,
    59,  0,   107, 0,   90,  25,  0,   0,   114, 277, 0,   4,   37,  192, 0,   0,   0,   86,  0,
    0,   182, 109, 139, 149, 0,   0,   0,   0,   0,   82,  0,   404, 0,   14,  55,  200, 0,   0,
    301, 12,  0,   28,  0,   0,   0,   68,  382};

int UnmangledHashG(const char *key, const int *T)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += T[i] * key[i];
        sum %= 427;
    }
    return unmangledkG[sum];
}

int UnmangledPerfectHash(const char *key)
{
    if (strlen(key) > 26)
        return 0;

    return (UnmangledHashG(key, unmangledkT1) + UnmangledHashG(key, unmangledkT2)) % 427;
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
