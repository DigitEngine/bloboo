
#define BLBOO_R(name,hex,attr)\
const unsigned char name[]=\
{\
0,  0,(hex)+0,attr,\
8,  0,(hex)+1,attr,\
16, 0,(hex)+0,attr|OAM_FLIP_H,\
0,  8,(hex)+2,attr,\
8,  8,(hex)+3,attr,\
16, 8,(hex)+4,attr,\
0, 16,(hex)+5,attr,\
8, 16,(hex)+6,attr,\
16,16,(hex)+7,attr,\
128};

#define BLBOO_L(name,hex,attr)\
const unsigned char name[]=\
{\
0,  0,(hex)+0,attr,\
8,  0,(hex)+1,attr|OAM_FLIP_H,\
16, 0,(hex)+0,attr|OAM_FLIP_H,\
0,  8,(hex)+4,attr|OAM_FLIP_H,\
8,  8,(hex)+3,attr|OAM_FLIP_H,\
16, 8,(hex)+2,attr|OAM_FLIP_H,\
0, 16,(hex)+7,attr|OAM_FLIP_H,\
8, 16,(hex)+6,attr|OAM_FLIP_H,\
16,16,(hex)+5,attr|OAM_FLIP_H,\
128};

#define BLBOO_HURT_R(name,hex,attr)\
const unsigned char name[]=\
{\
0,  0,(hex)+0 ,attr,\
8,  0,(hex)+1 ,attr,\
16, 0,(hex)+0 ,attr|OAM_FLIP_H,\
0,  8,(hex)+16,attr,\
8,  8,(hex)+17,attr,\
16, 8,(hex)+18,attr,\
0, 16,(hex)+19,attr,\
8, 16,(hex)+20,attr,\
16,16,(hex)+21,attr,\
128};

#define BLBOO_HURT_L(name,hex,attr)\
const unsigned char name[]=\
{\
0,  0,(hex)+0 ,attr,\
8,  0,(hex)+1 ,attr|OAM_FLIP_H,\
16, 0,(hex)+0 ,attr|OAM_FLIP_H,\
0,  8,(hex)+18,attr|OAM_FLIP_H,\
8,  8,(hex)+17,attr|OAM_FLIP_H,\
16, 8,(hex)+16,attr|OAM_FLIP_H,\
0, 16,(hex)+21,attr|OAM_FLIP_H,\
8, 16,(hex)+20,attr|OAM_FLIP_H,\
16,16,(hex)+19,attr|OAM_FLIP_H,\
128};


#define MSPR_3x3_BLANK(name)\
const unsigned char name[] = \
{\
0,  0,0xff,0,\
8,  0,0xff,0,\
16, 0,0xff,0,\
0,  8,0xff,0,\
8,  8,0xff,0,\
16, 8,0xff,0,\
0, 16,0xff,0,\
8, 16,0xff,0,\
16,16,0xff,0,\
128};
#define MSPR_2x2_BLANK(name)\
const unsigned char name[] = \
{\
0,  0,0xff,0,\
8,  0,0xff,0,\
0,  8,0xff,0,\
8,  8,0xff,0,\
128};


/* METASPRITE DEFINITIONS */

/// Neutral sprites

MSPR_2x2_BLANK(_2x2_BLINK);
MSPR_3x3_BLANK(_3x3_BLINK);

/// Right-facing sprites

// Player sprites
BLBOO_R(PLYR_R, 0x00, 0);
BLBOO_R(PLYR_WALK_R, 0x08, 0);


/// Left-facing sprites

// Player sprites
BLBOO_L(PLYR_L, 0x00, 0);