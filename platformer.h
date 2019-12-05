/* PLATFORMER ENGINE */

#define ACCEL 0x19
#define GRAVITY 0x4b
#define MAX_SPEED 0x180
#define JUMP_VEL -0x600
#define MAX_RIGHT 0x7b00



#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
#define LEFT 0
#define RIGHT 1
unsigned char sprid;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned int temp5;
unsigned int temp6;
unsigned char eject_L;
unsigned char eject_R;
unsigned char eject_U;
unsigned char eject_D;
unsigned char direction = RIGHT;

byte pad;
byte pad_t;

int address;
unsigned char x;
unsigned char y;
unsigned char nt;
unsigned char index;
unsigned char index2;
unsigned char room;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count;
unsigned int pseudo_scroll_x;
unsigned char L_R_switch;
unsigned char old_x;

unsigned char temp_x;
unsigned char temp_y;
unsigned char song;

unsigned char game_mode;
enum { MODE_GAME, MODE_PAUSE };

unsigned char coins;
const unsigned char* pointer;


#pragma bss-name(push, "BSS")

unsigned char c_map[240];
unsigned char c_map2[240];

struct Base
{
  unsigned char x;
  unsigned char y;
  unsigned char width;
  unsigned char height;
};

struct Base Generic;
struct Base Generic2;

struct Hero
{
  unsigned int x;
  unsigned int y;
  signed int vel_x;
  signed int vel_y;
};

struct Hero Bloboo = { 0x9ff, 0x9000 };


#define HERO_WIDTH 20
#define HERO_HEIGHT 24

#define TURN_OFF 0xff

// Coins & Enemies

const unsigned char metatiles_lvl1[] =
{
  0x00, 0x00, 0x00, 0x00, 0,
  0x51, 0x51, 0x61, 0x61, 0,
  0x52, 0x52, 0x62, 0x62, 0,
  0x53, 0x53, 0x63, 0x63, 0,
  0x54, 0x54, 0x64, 0x64, 0,
  0x32, 0x33, 0x42, 0x43, 0,
  0x30, 0x31, 0x40, 0x41, 0,
  0x34, 0x35, 0x44, 0x45, 0,
  0x55, 0x37, 0x55, 0x37, 1,
  0x55, 0x37, 0x57, 0x47, 1,
  0x36, 0x37, 0x46, 0x47, 1,
  0x36, 0x56, 0x46, 0x58, 1,
  0x36, 0x56, 0x36, 0x56, 1,
  0x38, 0x39, 0x38, 0x39, 1
};

#define COL_DOWN 0x80
#define COL_ALL 0x40

const unsigned char is_solid[] =
{
  0, 
  COL_DOWN,
  COL_ALL+COL_DOWN,
  COL_DOWN,
  COL_DOWN,
  COL_DOWN,
  0,
  0,
  0,
  0,
  0,
  0
};

#define MAX_ROOMS (4-1)
#define MAX_SCROLL (MAX_ROOMS*0x100)-1

const unsigned char* const Cols[] = {Col1_1, Col1_2, Col1_3, Col1_4};
const unsigned char* const Rooms[] = {Room1_1, Room1_2, Room1_3, Room1_4};

// PROTOTYPES
void load_room(void);
void draw_sprites(void);
void movement(void);
void bg_collision(void);
void draw_screen_R(void);
void new_cmap(void);
void bg_collision_sub(void);
void bg_check_low(void);
char get_position(void);
//void enemy_moves(void);
void sprite_collisions(void);
void check_spr_objects(void);
//void sprite_obj_init(void);