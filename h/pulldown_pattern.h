//////////////////////////////////////////////////////////////////////////////////
//	Pull down pattern 1
// basic pattern
#define PULLDOWN_PATTERN1_TOP	0x09
#define PULLDOWN_PATTERN1_BTM	0x09

// basic pattern x 2
#define PULLDOWN_PATTERN1_TOP_VER	0x129
#define PULLDOWN_PATTERN1_BTM_VER	0x129

// pattern variations: 5
#define PULLDOWN_PATTER1_VARIATIONS	(5)
static UINT16 pulldown_pattern1_top_vers[] = {(PULLDOWN_PATTERN1_TOP_VER & 0x3ff),
											((PULLDOWN_PATTERN1_TOP_VER >> 1) & 0x3ff),
											((PULLDOWN_PATTERN1_TOP_VER >> 2) & 0x3ff),
											((PULLDOWN_PATTERN1_TOP_VER >> 3) & 0x3ff),
											((PULLDOWN_PATTERN1_TOP_VER >> 4) & 0x3ff)};

static UINT16 pulldown_pattern1_btm_vers[] = {(PULLDOWN_PATTERN1_BTM_VER & 0x3ff),
											((PULLDOWN_PATTERN1_BTM_VER >> 1) & 0x3ff),
											((PULLDOWN_PATTERN1_BTM_VER >> 2) & 0x3ff),
											((PULLDOWN_PATTERN1_BTM_VER >> 3) & 0x3ff),
											((PULLDOWN_PATTERN1_BTM_VER >> 4) & 0x3ff)};

//////////////////////////////////////////////////////////////////////////////////
//	Pull down pattern 2
//	- pattern length 5
//		T0 T0 T1 T2 T3		TOP: 00|1100|0000	0xC0
//		B0 B1 B2 B2 B3		BTM: 00|0000|1100	0x0C
// basic pattern
#define PULLDOWN_PATTERN2_TOP	0xc0
#define PULLDOWN_PATTERN2_BTM	0x0c

// basic pattern x 2
#define PULLDOWN_PATTERN2_TOP_VER	0x300c0
#define PULLDOWN_PATTERN2_BTM_VER	0x0300c

// pattern variations: 10
#define PULLDOWN_PATTER2_VARIATIONS	(10)
static UINT16 pulldown_pattern2_top_vers[] = {(PULLDOWN_PATTERN2_TOP_VER & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 9) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 8) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 7) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 6) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 5) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 4) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 3) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 2) & 0x3ff),
											((PULLDOWN_PATTERN2_TOP_VER >> 1) & 0x3ff)};
static UINT16 pulldown_pattern2_btm_vers[] = {(PULLDOWN_PATTERN2_BTM_VER & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 9) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 8) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 7) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 6) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 5) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 4) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 3) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 2) & 0x3ff),
											((PULLDOWN_PATTERN2_BTM_VER >> 1) & 0x3ff)};

//////////////////////////////////////////////////////////////////////////////////
//	Pull down pattern 4	-	top first pattern
//	- pattern length 5
//		T0 T0 T1 T2 T3		TOP: 00|1100|0000	0xC0
//		B0 B1 B2 B3 B3		BTM: 00|0000|0011	0x03
// basic pattern
#define PULLDOWN_PATTERN4_TOP	0xc0
#define PULLDOWN_PATTERN4_BTM	0x03

// basic pattern x 2
#define PULLDOWN_PATTERN4_TOP_VER	0x300c0
#define PULLDOWN_PATTERN4_BTM_VER	0x00c03

// pattern variations: 10
#define PULLDOWN_PATTER4_VARIATIONS	(10)
static UINT16 pulldown_pattern4_top_vers[] = {(PULLDOWN_PATTERN4_TOP_VER & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 9) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 8) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 7) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 6) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 5) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 4) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 3) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 2) & 0x3ff),
											((PULLDOWN_PATTERN4_TOP_VER >> 1) & 0x3ff)};
static UINT16 pulldown_pattern4_btm_vers[] = {(PULLDOWN_PATTERN4_BTM_VER & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 9) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 8) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 7) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 6) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 5) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 4) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 3) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 2) & 0x3ff),
											((PULLDOWN_PATTERN4_BTM_VER >> 1) & 0x3ff)};
/*
//////////////////////////////////////////////////////////////////////////////////
//	Pull down patter 6	-	bottom first pattern
//	- pattern length 5
//		T0 T1 T2 T3 T3		BTM: 00|0000|0011	0x03
//		B0 B1 B1 B2 B3		TOP: 00|0011|0000	0x03
// basic pattern
#define PULLDOWN_PATTERN6_TOP	0x0c
#define PULLDOWN_PATTERN6_BTM	0xc0

// basic pattern x 2
#define PULLDOWN_PATTERN4_TOP_VER	0x300c0
#define PULLDOWN_PATTERN4_BTM_VER	0x00c03
// pattern variations: 10
#define PULLDOWN_PATTERN4_TOP_VER0	(PULLDOWN_PATTERN4_TOP_VER & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER0	(PULLDOWN_PATTERN4_BTM_VER & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER1	((PULLDOWN_PATTERN4_TOP_VER >> 1) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER1	((PULLDOWN_PATTERN4_BTM_VER >> 1) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER2	((PULLDOWN_PATTERN4_TOP_VER >> 2) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER2	((PULLDOWN_PATTERN4_BTM_VER >> 2) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER3	((PULLDOWN_PATTERN4_TOP_VER >> 3) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER3	((PULLDOWN_PATTERN4_BTM_VER >> 3) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER4	((PULLDOWN_PATTERN4_TOP_VER >> 4) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER4	((PULLDOWN_PATTERN4_BTM_VER >> 4) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER5	((PULLDOWN_PATTERN4_TOP_VER >> 5) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER5	((PULLDOWN_PATTERN4_BTM_VER >> 5) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER6	((PULLDOWN_PATTERN4_TOP_VER >> 6) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER6	((PULLDOWN_PATTERN4_BTM_VER >> 6) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER7	((PULLDOWN_PATTERN4_TOP_VER >> 7) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER7	((PULLDOWN_PATTERN4_BTM_VER >> 7) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER8	((PULLDOWN_PATTERN4_TOP_VER >> 8) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER8	((PULLDOWN_PATTERN4_BTM_VER >> 8) & 0x3ff)
#define PULLDOWN_PATTERN4_TOP_VER9	((PULLDOWN_PATTERN4_TOP_VER >> 9) & 0x3ff)
#define PULLDOWN_PATTERN4_BTM_VER9	((PULLDOWN_PATTERN4_BTM_VER >> 9) & 0x3ff)

*/

