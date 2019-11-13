/* PLATFORMER ENGINE */

#define ACCEL 0x30
#define GRAVITY 0x50
#define MAX_SPEED 0x240
#define JUMP_VEL -0x600
#define MAX_RIGHT 0x8000



#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char sprid;
unsigned char pad_t;
unsigned char pad;
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
unsigned char direction;
#define LEFT 0
#define RIGHT 1

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

struct Hero Bloboo = { 0x9ff, 0xa000 };


#define HERO_WIDTH 11
#define HERO_HEIGHT 12

#define TURN_OFF 0xff

// Coins & Enemies

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

#define MAX_ROOMS 1
#define MAX_SCROLL (MAX_ROOMS*0x100)-1

const unsigned char* Rooms[] = {0};