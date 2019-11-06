
#define MSPR_2x2(name,hex,attr)\
const unsigned char name[] = \
{\
0,0,(hex)+0,attr,\
8,0,(hex)+1,attr,\
0,8,(hex)+2,attr,\
8,8,(hex)+3,attr,\
128};
#define MSPR_2x2_FLIP(name,hex,attr)\
const unsigned char name[] = \
{\
8,0,(hex)+0,attr|OAM_FLIP_H,\
0,0,(hex)+1,attr|OAM_FLIP_H,\
8,8,(hex)+2,attr|OAM_FLIP_H,\
0,8,(hex)+3,attr|OAM_FLIP_H,\
128};
#define MSPR_3x3(name,hex,attr)\
const unsigned char name[] = \
{\
0,  0,(hex)+0,attr,\
8,  0,(hex)+1,attr,\
16, 0,(hex)+2,attr,\
0,  8,(hex)+3,attr,\
8,  8,(hex)+4,attr,\
16, 8,(hex)+5,attr,\
0, 16,(hex)+6,attr,\
8, 16,(hex)+7,attr,\
16,16,(hex)+8,attr,\
128};
#define MSPR_3x3_FLIP(name,hex,attr)\
const unsigned char name[] = \
{\
16, 0,(hex)+0,attr|OAM_FLIP_H,\
8,  0,(hex)+1,attr|OAM_FLIP_H,\
0,  0,(hex)+2,attr|OAM_FLIP_H,\
16, 8,(hex)+3,attr|OAM_FLIP_H,\
8,  8,(hex)+4,attr|OAM_FLIP_H,\
0,  8,(hex)+5,attr|OAM_FLIP_H,\
16,16,(hex)+6,attr|OAM_FLIP_H,\
8, 16,(hex)+7,attr|OAM_FLIP_H,\
0, 16,(hex)+8,attr|OAM_FLIP_H,\
128};
#define MSPR_3x3_SAME(name)\
const unsigned char name[] = \
{\
0,  0,0x00,0,\
8,  0,0x00,0,\
16, 0,0x00,0,\
0,  8,0x00,0,\
8,  8,0x00,0,\
16, 8,0x00,0,\
0, 16,0x00,0,\
8, 16,0x00,0,\
16,16,0x00,0,\
128};
#define MSPR_2x2_SAME(name)\
const unsigned char name[] = \
{\
0,  0,0x00,0,\
8,  0,0x00,0,\
0,  8,0x00,0,\
8,  8,0x00,0,\
128};


/* METASPRITE DEFINITIONS */

/// Neutral sprites

MSPR_2x2_SAME(_2x2_BLINK);
MSPR_3x3_SAME(_3x3_BLINK);

/// Right-facing sprites

// Player sprites
MSPR_3x3(PLAYER_R, 0x70, 0);
MSPR_3x3(PLYR_WALK_R, 0x80, 0);
MSPR_3x3(PLYR_HURT_R, 0x90, 0);

// Enemy 1 sprites
MSPR_2x2(ENEMY1_1_R, 0xa0, 1);
MSPR_2x2(ENEMY1_2_R, 0xa4, 1);

/// Left-facing sprites

// Player sprites
MSPR_3x3_FLIP(PLAYER_L, 0x70, 0);
MSPR_3x3_FLIP(PLAYER_WALK_L, 0x80, 0);
MSPR_3x3_FLIP(PLAYER_HURT_L, 0x90, 0);

// Enemy 1 sprites
MSPR_2x2_FLIP(ENEMY_1_1_L, 0xa0, 1);
MSPR_2x2_FLIP(ENEMY_1_2_L, 0xa4, 1);