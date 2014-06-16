/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "vp9/common/vp9_common.h"
#include "vp9/common/vp9_quant_common.h"
#include "vp9/common/vp9_seg_common.h"

#if 1
static const int16_t dc_qlookup[QINDEX_RANGE] = {
  4,       8,    8,    9,   10,   11,   12,   12,
  13,     14,   15,   16,   17,   18,   19,   19,
  20,     21,   22,   23,   24,   25,   26,   26,
  27,     28,   29,   30,   31,   32,   32,   33,
  34,     35,   36,   37,   38,   38,   39,   40,
  41,     42,   43,   43,   44,   45,   46,   47,
  48,     48,   49,   50,   51,   52,   53,   53,
  54,     55,   56,   57,   57,   58,   59,   60,
  61,     62,   62,   63,   64,   65,   66,   66,
  67,     68,   69,   70,   70,   71,   72,   73,
  74,     74,   75,   76,   77,   78,   78,   79,
  80,     81,   81,   82,   83,   84,   85,   85,
  87,     88,   90,   92,   93,   95,   96,   98,
  99,    101,  102,  104,  105,  107,  108,  110,
  111,   113,  114,  116,  117,  118,  120,  121,
  123,   125,  127,  129,  131,  134,  136,  138,
  140,   142,  144,  146,  148,  150,  152,  154,
  156,   158,  161,  164,  166,  169,  172,  174,
  177,   180,  182,  185,  187,  190,  192,  195,
  199,   202,  205,  208,  211,  214,  217,  220,
  223,   226,  230,  233,  237,  240,  243,  247,
  250,   253,  257,  261,  265,  269,  272,  276,
  280,   284,  288,  292,  296,  300,  304,  309,
  313,   317,  322,  326,  330,  335,  340,  344,
  349,   354,  359,  364,  369,  374,  379,  384,
  389,   395,  400,  406,  411,  417,  423,  429,
  435,   441,  447,  454,  461,  467,  475,  482,
  489,   497,  505,  513,  522,  530,  539,  549,
  559,   569,  579,  590,  602,  614,  626,  640,
  654,   668,  684,  700,  717,  736,  755,  775,
  796,   819,  843,  869,  896,  925,  955,  988,
  1022, 1058, 1098, 1139, 1184, 1232, 1282, 1336,
};

#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
static const int16_t dc_qlookup_10[QINDEX_RANGE_10] = {
  4,     8,     8,     9,     10,    11,    12,    13,
  13,    14,    15,    16,    17,    18,    19,    20,
  21,    22,    22,    23,    24,    25,    26,    27,
  28,    29,    30,    30,    31,    32,    33,    34,
  35,    36,    37,    38,    38,    39,    40,    41,
  42,    43,    44,    45,    45,    46,    47,    48,
  49,    50,    51,    52,    53,    53,    54,    55,
  56,    57,    58,    59,    60,    60,    61,    62,
  63,    64,    65,    66,    67,    67,    68,    69,
  70,    71,    72,    73,    74,    74,    75,    76,
  77,    78,    79,    80,    81,    81,    82,    83,
  84,    85,    86,    87,    88,    88,    89,    90,
  92,    94,    95,    97,    99,    101,   102,   104,
  106,   107,   109,   111,   113,   114,   116,   118,
  119,   121,   123,   125,   126,   128,   130,   131,
  133,   136,   138,   141,   143,   146,   148,   151,
  153,   156,   159,   161,   164,   166,   169,   171,
  174,   176,   180,   183,   186,   190,   193,   196,
  199,   203,   206,   209,   213,   216,   219,   223,
  227,   232,   236,   240,   244,   248,   252,   256,
  260,   265,   270,   274,   279,   284,   289,   294,
  298,   303,   309,   314,   320,   325,   331,   336,
  341,   348,   354,   360,   366,   372,   378,   385,
  392,   399,   406,   413,   419,   427,   434,   442,
  449,   456,   464,   473,   481,   489,   496,   505,
  514,   522,   531,   540,   549,   558,   567,   577,
  587,   596,   606,   616,   626,   637,   647,   658,
  669,   680,   691,   702,   714,   725,   737,   749,
  761,   773,   785,   798,   811,   824,   836,   850,
  863,   877,   890,   904,   918,   933,   947,   962,
  976,   992,   1007,  1022,  1037,  1053,  1069,  1085,
  1101,  1117,  1133,  1150,  1167,  1184,  1201,  1219,
  1236,  1254,  1272,  1291,  1309,  1328,  1347,  1366,
  1385,  1405,  1425,  1445,  1465,  1486,  1507,  1528,
  1550,  1572,  1595,  1618,  1641,  1664,  1689,  1713,
  1738,  1764,  1790,  1816,  1844,  1872,  1901,  1930,
  1961,  1992,  2025,  2058,  2093,  2129,  2166,  2205,
  2245,  2287,  2330,  2376,  2423,  2473,  2526,  2580,
  2638,  2699,  2763,  2830,  2902,  2976,  3055,  3139,
  3228,  3322,  3423,  3529,  3641,  3761,  3889,  4024,
  4169,  4323,  4488,  4663,  4850,  5049,  5262,  5489,
};

static const int16_t dc_qlookup_12[QINDEX_RANGE_12] = {
  4,     8,     8,     9,     10,    11,    12,    13,
  13,    14,    15,    16,    17,    18,    19,    20,
  21,    22,    22,    23,    24,    25,    26,    27,
  28,    29,    30,    31,    31,    32,    33,    34,
  35,    36,    37,    38,    39,    40,    40,    41,
  42,    43,    44,    45,    46,    47,    48,    48,
  49,    50,    51,    52,    53,    54,    55,    56,
  57,    57,    58,    59,    60,    61,    62,    63,
  64,    65,    65,    66,    67,    68,    69,    70,
  71,    72,    73,    74,    74,    75,    76,    77,
  78,    79,    80,    81,    82,    82,    83,    84,
  85,    86,    87,    88,    89,    90,    90,    91,
  93,    95,    97,    99,    100,   102,   104,   106,
  107,   109,   111,   113,   115,   116,   118,   120,
  122,   123,   125,   127,   129,   131,   132,   134,
  136,   139,   141,   144,   147,   149,   152,   154,
  157,   160,   162,   165,   168,   170,   173,   176,
  178,   181,   185,   188,   192,   195,   199,   202,
  206,   209,   213,   216,   220,   223,   227,   231,
  236,   240,   244,   249,   253,   258,   262,   266,
  271,   276,   281,   287,   292,   297,   302,   307,
  313,   318,   324,   330,   336,   342,   348,   354,
  361,   367,   374,   381,   388,   395,   402,   410,
  418,   425,   433,   441,   449,   457,   466,   474,
  483,   491,   501,   510,   520,   529,   538,   549,
  559,   569,   579,   590,   601,   612,   623,   635,
  647,   659,   670,   683,   695,   708,   721,   735,
  748,   762,   776,   790,   805,   820,   835,   851,
  866,   882,   898,   915,   932,   949,   966,   984,
  1002,  1020,  1039,  1058,  1078,  1098,  1118,  1138,
  1159,  1180,  1202,  1224,  1246,  1269,  1292,  1315,
  1339,  1363,  1388,  1412,  1438,  1464,  1490,  1517,
  1544,  1572,  1600,  1628,  1658,  1687,  1717,  1747,
  1778,  1809,  1841,  1873,  1906,  1940,  1974,  2008,
  2043,  2079,  2115,  2152,  2190,  2228,  2266,  2305,
  2344,  2384,  2425,  2466,  2508,  2550,  2593,  2637,
  2681,  2726,  2771,  2817,  2864,  2911,  2959,  3007,
  3057,  3106,  3157,  3208,  3260,  3312,  3366,  3419,
  3474,  3529,  3585,  3641,  3699,  3756,  3815,  3874,
  3934,  3995,  4056,  4118,  4181,  4244,  4308,  4373,
  4439,  4505,  4572,  4640,  4709,  4778,  4848,  4919,
  4991,  5064,  5137,  5212,  5287,  5363,  5440,  5518,
  5597,  5677,  5758,  5840,  5923,  6008,  6093,  6180,
  6268,  6358,  6449,  6542,  6636,  6732,  6831,  6931,
  7033,  7138,  7245,  7355,  7467,  7583,  7702,  7824,
  7949,  8079,  8213,  8352,  8496,  8645,  8800,  8960,
  9128,  9303,  9485,  9675,  9875,  10083, 10303, 10533,
  10775, 11030, 11299, 11583, 11883, 12200, 12536, 12891,
  13269, 13668, 14093, 14545, 15024, 15535, 16078, 16657,
  17273, 17930, 18632, 19380, 20179, 21032, 21943,
};
#endif

static const int16_t ac_qlookup[QINDEX_RANGE] = {
  4,       8,    9,   10,   11,   12,   13,   14,
  15,     16,   17,   18,   19,   20,   21,   22,
  23,     24,   25,   26,   27,   28,   29,   30,
  31,     32,   33,   34,   35,   36,   37,   38,
  39,     40,   41,   42,   43,   44,   45,   46,
  47,     48,   49,   50,   51,   52,   53,   54,
  55,     56,   57,   58,   59,   60,   61,   62,
  63,     64,   65,   66,   67,   68,   69,   70,
  71,     72,   73,   74,   75,   76,   77,   78,
  79,     80,   81,   82,   83,   84,   85,   86,
  87,     88,   89,   90,   91,   92,   93,   94,
  95,     96,   97,   98,   99,  100,  101,  102,
  104,   106,  108,  110,  112,  114,  116,  118,
  120,   122,  124,  126,  128,  130,  132,  134,
  136,   138,  140,  142,  144,  146,  148,  150,
  152,   155,  158,  161,  164,  167,  170,  173,
  176,   179,  182,  185,  188,  191,  194,  197,
  200,   203,  207,  211,  215,  219,  223,  227,
  231,   235,  239,  243,  247,  251,  255,  260,
  265,   270,  275,  280,  285,  290,  295,  300,
  305,   311,  317,  323,  329,  335,  341,  347,
  353,   359,  366,  373,  380,  387,  394,  401,
  408,   416,  424,  432,  440,  448,  456,  465,
  474,   483,  492,  501,  510,  520,  530,  540,
  550,   560,  571,  582,  593,  604,  615,  627,
  639,   651,  663,  676,  689,  702,  715,  729,
  743,   757,  771,  786,  801,  816,  832,  848,
  864,   881,  898,  915,  933,  951,  969,  988,
  1007, 1026, 1046, 1066, 1087, 1108, 1129, 1151,
  1173, 1196, 1219, 1243, 1267, 1292, 1317, 1343,
  1369, 1396, 1423, 1451, 1479, 1508, 1537, 1567,
  1597, 1628, 1660, 1692, 1725, 1759, 1793, 1828,
};

#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
static const int16_t ac_qlookup_10[QINDEX_RANGE_10] = {
  4,     8,     9,     10,    11,    12,    13,    14,
  15,    16,    17,    18,    19,    20,    21,    22,
  23,    24,    25,    26,    27,    28,    29,    30,
  31,    32,    33,    34,    35,    36,    37,    38,
  39,    40,    41,    42,    43,    44,    45,    46,
  47,    48,    49,    50,    51,    52,    53,    54,
  55,    56,    57,    58,    59,    60,    61,    62,
  63,    64,    65,    66,    67,    68,    69,    70,
  71,    72,    73,    74,    75,    76,    77,    78,
  79,    80,    81,    82,    83,    84,    85,    86,
  87,    88,    89,    90,    91,    92,    93,    94,
  95,    96,    97,    98,    99,    100,   101,   102,
  104,   106,   108,   110,   112,   114,   116,   118,
  120,   122,   124,   126,   128,   130,   132,   134,
  136,   138,   140,   142,   144,   146,   148,   150,
  152,   155,   158,   161,   164,   167,   170,   173,
  176,   179,   182,   185,   188,   191,   194,   197,
  200,   203,   207,   211,   215,   219,   223,   227,
  231,   235,   239,   243,   247,   251,   255,   260,
  265,   270,   275,   280,   285,   290,   295,   300,
  305,   311,   317,   323,   329,   335,   341,   347,
  353,   359,   366,   373,   380,   387,   394,   401,
  408,   416,   424,   432,   440,   448,   456,   465,
  474,   483,   492,   501,   510,   520,   530,   540,
  550,   560,   571,   582,   593,   604,   615,   627,
  639,   651,   663,   676,   689,   702,   715,   729,
  743,   757,   771,   786,   801,   816,   832,   848,
  864,   881,   898,   915,   933,   951,   969,   988,
  1007,  1026,  1046,  1066,  1087,  1108,  1129,  1151,
  1173,  1196,  1219,  1243,  1267,  1292,  1317,  1343,
  1369,  1396,  1423,  1451,  1479,  1508,  1537,  1567,
  1597,  1628,  1660,  1692,  1725,  1759,  1793,  1828,
  1864,  1900,  1937,  1975,  2014,  2053,  2093,  2134,
  2176,  2218,  2261,  2305,  2350,  2396,  2443,  2491,
  2540,  2590,  2641,  2693,  2746,  2800,  2855,  2911,
  2968,  3026,  3085,  3145,  3207,  3270,  3334,  3399,
  3466,  3534,  3603,  3674,  3746,  3819,  3894,  3970,
  4048,  4127,  4208,  4291,  4375,  4461,  4549,  4638,
  4729,  4822,  4917,  5014,  5113,  5213,  5315,  5419,
  5526,  5635,  5746,  5859,  5974,  6091,  6211,  6333,
  6458,  6585,  6715,  6847,  6982,  7119,  7259,  7402,
};

static const int16_t ac_qlookup_12[QINDEX_RANGE_12] = {
  4,     8,     9,     10,    11,    12,    13,    14,
  15,    16,    17,    18,    19,    20,    21,    22,
  23,    24,    25,    26,    27,    28,    29,    30,
  31,    32,    33,    34,    35,    36,    37,    38,
  39,    40,    41,    42,    43,    44,    45,    46,
  47,    48,    49,    50,    51,    52,    53,    54,
  55,    56,    57,    58,    59,    60,    61,    62,
  63,    64,    65,    66,    67,    68,    69,    70,
  71,    72,    73,    74,    75,    76,    77,    78,
  79,    80,    81,    82,    83,    84,    85,    86,
  87,    88,    89,    90,    91,    92,    93,    94,
  95,    96,    97,    98,    99,    100,   101,   102,
  104,   106,   108,   110,   112,   114,   116,   118,
  120,   122,   124,   126,   128,   130,   132,   134,
  136,   138,   140,   142,   144,   146,   148,   150,
  152,   155,   158,   161,   164,   167,   170,   173,
  176,   179,   182,   185,   188,   191,   194,   197,
  200,   203,   207,   211,   215,   219,   223,   227,
  231,   235,   239,   243,   247,   251,   255,   260,
  265,   270,   275,   280,   285,   290,   295,   300,
  305,   311,   317,   323,   329,   335,   341,   347,
  353,   359,   366,   373,   380,   387,   394,   401,
  408,   416,   424,   432,   440,   448,   456,   465,
  474,   483,   492,   501,   510,   520,   530,   540,
  550,   560,   571,   582,   593,   604,   615,   627,
  639,   651,   663,   676,   689,   702,   715,   729,
  743,   757,   771,   786,   801,   816,   832,   848,
  864,   881,   898,   915,   933,   951,   969,   988,
  1007,  1026,  1046,  1066,  1087,  1108,  1129,  1151,
  1173,  1196,  1219,  1243,  1267,  1292,  1317,  1343,
  1369,  1396,  1423,  1451,  1479,  1508,  1537,  1567,
  1597,  1628,  1660,  1692,  1725,  1759,  1793,  1828,
  1864,  1900,  1937,  1975,  2014,  2053,  2093,  2134,
  2176,  2218,  2261,  2305,  2350,  2396,  2443,  2491,
  2540,  2590,  2641,  2693,  2746,  2800,  2855,  2911,
  2968,  3026,  3085,  3145,  3207,  3270,  3334,  3399,
  3466,  3534,  3603,  3674,  3746,  3819,  3894,  3970,
  4048,  4127,  4208,  4291,  4375,  4461,  4549,  4638,
  4729,  4822,  4917,  5014,  5113,  5213,  5315,  5419,
  5526,  5635,  5746,  5859,  5974,  6091,  6211,  6333,
  6458,  6585,  6715,  6847,  6982,  7119,  7259,  7402,
  7548,  7697,  7849,  8004,  8162,  8323,  8487,  8654,
  8824,  8998,  9175,  9356,  9540,  9728,  9920,  10115,
  10314, 10517, 10724, 10935, 11150, 11370, 11594, 11822,
  12055, 12293, 12535, 12782, 13034, 13291, 13553, 13820,
  14092, 14370, 14653, 14942, 15237, 15537, 15843, 16155,
  16474, 16799, 17130, 17468, 17812, 18163, 18521, 18886,
  19258, 19638, 20025, 20420, 20823, 21234, 21653, 22080,
  22516, 22960, 23413, 23875, 24346, 24826, 25316, 25815,
  26324, 26843, 27373, 27913, 28464, 29026, 29599,
};
#endif

void vp9_init_quant_tables(void) { }
#else
static int16_t dc_qlookup[QINDEX_RANGE];
static int16_t ac_qlookup[QINDEX_RANGE];

#define ACDC_MIN 8

// TODO(dkovalev) move to common and reuse
static double poly3(double a, double b, double c, double d, double x) {
  return a*x*x*x + b*x*x + c*x + d;
}

void vp9_init_quant_tables() {
  int i, val = 4;

  // A "real" q of 1.0 forces lossless mode.
  // In practice non lossless Q's between 1.0 and 2.0 (represented here by
  // integer values from 5-7 give poor rd results (lower psnr and often
  // larger size than the lossless encode. To block out those "not very useful"
  // values we increment the ac and dc q lookup values by 4 after position 0.
  ac_qlookup[0] = val;
  dc_qlookup[0] = val;
  val += 4;

  for (i = 1; i < QINDEX_RANGE; i++) {
    const int ac_val = val;

    val = (int)(val * 1.01975);
    if (val == ac_val)
      ++val;

    ac_qlookup[i] = (int16_t)ac_val;
    dc_qlookup[i] = (int16_t)MAX(ACDC_MIN, poly3(0.000000305, -0.00065, 0.9,
                                                 0.5, ac_val));
  }
}
#endif

int16_t vp9_dc_quant(int qindex, int delta, vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return dc_qlookup_10[clamp(qindex + delta, 0, MAXQ_10)];
    case VPX_BITS_12:
      return dc_qlookup_12[clamp(qindex + delta, 0, MAXQ_12)];
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#elif CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS
  switch (bit_depth) {
    case VPX_BITS_8:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)] << 2;
    case VPX_BITS_12:
      return dc_qlookup[clamp(qindex + delta, 0, MAXQ)] << 4;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return dc_qlookup[clamp(qindex + delta, 0, MAXQ)];
#endif
}

int16_t vp9_ac_quant(int qindex, int delta, vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return ac_qlookup_10[clamp(qindex + delta, 0, MAXQ_10)];
    case VPX_BITS_12:
      return ac_qlookup_12[clamp(qindex + delta, 0, MAXQ_12)];
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#elif CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS
  switch (bit_depth) {
    case VPX_BITS_8:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)];
    case VPX_BITS_10:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)] << 2;
    case VPX_BITS_12:
      return ac_qlookup[clamp(qindex + delta, 0, MAXQ)] << 4;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return ac_qlookup[clamp(qindex + delta, 0, MAXQ)];
#endif
}

int vp9_get_qindex(const struct segmentation *seg, int segment_id,
                   int base_qindex, vpx_bit_depth_t bit_depth) {
  if (vp9_segfeature_active(seg, segment_id, SEG_LVL_ALT_Q)) {
    const int data = vp9_get_segdata(seg, segment_id, SEG_LVL_ALT_Q);
    const int seg_qindex = seg->abs_delta == SEGMENT_ABSDATA ?
        data : base_qindex + data;
    return clamp(seg_qindex, 0, vp9_get_maxq(bit_depth));
  } else {
    return base_qindex;
  }
}


int vp9_get_maxq(vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return MAXQ;
    case VPX_BITS_10:
      return MAXQ_10;
    case VPX_BITS_12:
      return MAXQ_12;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return MAXQ;
#endif
}

int vp9_get_qindex_range(vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return QINDEX_RANGE;
    case VPX_BITS_10:
      return QINDEX_RANGE_10;
    case VPX_BITS_12:
      return QINDEX_RANGE_12;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return QINDEX_RANGE;
#endif
}

int vp9_get_qindex_bits(vpx_bit_depth_t bit_depth) {
#if CONFIG_VP9_HIGH && CONFIG_HIGH_TRANSFORMS && CONFIG_HIGH_QUANT
  switch (bit_depth) {
    case VPX_BITS_8:
      return QINDEX_BITS;
    case VPX_BITS_10:
      return QINDEX_BITS_10;
    case VPX_BITS_12:
      return QINDEX_BITS_12;
    default:
      assert(0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12");
  }
#else
  (void) bit_depth;
  return QINDEX_BITS;
#endif
}
