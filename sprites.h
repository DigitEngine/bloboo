#define BSP 0x2d


#define BLBOO_R(name,hex,attr)\
const unsigned char name []=\
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

#define BLBOO_SHOOT_R(name,hex,attr)\
const unsigned char name[]=\
{\
0,  0,(hex)+0 ,attr,



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
const unsigned char paused_text[] =
{
0, 0,0x1a,0,
8, 0,0x0b,0,
16,0,0x1f,0,
24,0,0x1d,0,
32,0,0x0f,0,
40,0,0x0e,0,
128};
static unsigned char wlk_wait = 15;
unsigned char wlk_frame_num = 0;

bool is_walking = false;
/* METASPRITE DEFINITIONS */

/// Neutral sprites

MSPR_2x2_BLANK(_2x2_BLINK);
MSPR_3x3_BLANK(_3x3_BLINK);

/// Right-facing sprites

// Player sprites
BLBOO_R(BLB_R, 0x00, 0);		// Bloboo
BLBOO_R(BLB_WLK_R, 0x08, 0);
BLBOO_HURT_R(BLB_HRT_R, 0x00, 0);

BLBOO_R(KKE_R, 0x16, 0);		// Kookie
BLBOO_R(KKE_WLK_R, 0x1e, 0);
BLBOO_HURT_R(KKE_HRT_R, 0x16, 0);

/// Left-facing sprites

// Player sprites
BLBOO_L(BLB_L, 0x00, 0);		// Bloboo
BLBOO_L(BLB_WLK_L, 0x08, 0);
BLBOO_HURT_L(BLB_HRT_L, 0x00, 0);

BLBOO_L(KKE_L, 0x16, 0);		// Kookie
BLBOO_L(KKE_WLK_L, 0x1e, 0);
BLBOO_HURT_L(KKE_HRT_L, 0x16, 0);

unsigned char const* cur_spr_L = BLB_WLK_L;
unsigned char const* cur_spr_R = BLB_R;

void plyr_walk()
{
  if(wlk_wait)
  {
    wlk_wait--;
  }
  else
  {
    // Update frame number
    wlk_frame_num++;
    if(wlk_frame_num > 1)wlk_frame_num = 0;
    
    // Update left
    if(wlk_frame_num == 0)cur_spr_L = BLB_L;
    if(wlk_frame_num == 1)cur_spr_L = BLB_WLK_L;
    
    // Update right
    if(wlk_frame_num == 0)cur_spr_R = BLB_R;
    if(wlk_frame_num == 1)cur_spr_R = BLB_WLK_R;
    
    // Restart animation
    wlk_wait = 15;
  }
}