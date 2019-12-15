/*
- - -  I N F O  - - -
Name: The Adventures of Bloboo and Friends
Date Started: 10/13/2019
Build Date: ??/??/????
Copyright: MSDT Games
Author: Matthew T. Sbelgio, Declan J. Toole
Mapper: 0
Platform: NES
*/
#include "neslib.h"			// Main library

#include <string.h>			// Stuff with memory

// SCREEN NAMETABLES
#include "nametable_title.h"		// Title screen
#include "nametable_gameover.h"		// Game over screen
#include "nametable_winscreen.h"	// Winner screen
#include "nametable_levelselect.h"	// Level select

#include "nesdoug.h"			// NESDoug's library
//#link "nesdoug.s"

#include "sprites.h"			// Game sprites
#include "collisions.c"			// Collisions
#include "rooms.c"			// Rooms (Graphical)

#define NES_MIRRORING 1

#define TITLE     0x00	// Hex for title screen state
#define GAME      0x01	// Hex for game state
#define GAMEOVER  0x02	// Hex for game over state
#define WINSCREEN 0x03	// Hex for winner screen
#define LVLSELECT 0x04	// Hex for level select

#define SFX_SELECT     0
#define SFX_SELECT_YES 1
#define COMBO_ACCEPT   2

#define PLAYER_RIGHT 0x00
#define PLAYER_LEFT  0x01

#define PLAYER_NORMAL 0x00
#define PLAYER_HURT   0x01
#define PLAYER_UPSD   0x02

/*
- - -  L E V E L   D E F I N I T I O N S  - - -
These "#define" directives contain hexadecimal
numbers that stand for a different level in the
game. They should be used to assign a value to
the "level" variable. Do not use them for the
"state" variable, because numbers higher than
0x04 assigned to that variable will ultimately
result in the game not knowing what to do and
will most likely display garbage tiles.

Level 1 Forest
BOSS: Cursed Lil' Orange
HIDDEN PLACE(S): None
PEOPLE: Sweetie, Gramples, Lil' Orange

Level 2 Cave
BOSS: Giant lavender-colored snail
HIDDEN PLACE(S): None
PEOPLE: Shaky

Level 3 Egypt
BOSS: Giant Bloody Mummy
HIDDEN PLACE(S): 1
PEOPLE: None

Level 4 Beach
BOSS: Water Monster
HIDDEN PLACE(S): None
PEOPLE: Crazy, Jiggly

Level 5 Robot Factory
BOSS(ES): Giant Robot (Midboss), The TV Master (Boss) 
HIDDEN PLACE(S): 1
PEOPLE: None

Level 6 Foxie's Place/Magical Library
BOSS: Demon (Summoned)
HIDDEN PLACE(S): 2
PEOPLE: Foxie, Zappy, Flowy

LEVEL 7 Dark/Melancholy Jungle
BOSS: Angry Gorilla
HIDDEN PLACE(S): 1
PEOPLE: Hand Guy, Rollie

Level 8 Clocktower
BOSS: Survive
HIDDEN PLACE(S): None
PEOPLE: Blushy

Level 9 Prehistoric Jungle
BOSS: Poisonus Pterodactyl
HIDDEN PLACE(S): 1
PEOPLE: Dino guy

Level A Volcanic Planet
BOSS: Lava monster
HIDDEN PLACE(S): None
PEOPLE: Burny

Level B Icy Planet
BOSS: Survive
HIDDEN PLACE(S): 1
PEOPLE: None

Level C Giant Castle (FINAL LEVEL)
BOSS: Dark Bloboo (Midboss), Evil Warlock (Boss)
HIDDEN PLACE(S): 5
PEOPLE: None
*/
#define LEVEL_1 0x00	// Level 1 (Forest)
#define LEVEL_2 0x01	// Level 2 (Cave)
#define LEVEL_3 0x02	// Level 3 (Pyramid/Egypt)
#define LEVEL_4 0x03	// Level 4 (Beach)
#define LEVEL_5 0x04	// Level 5 (Robot Factory)
#define LEVEL_6 0x05  	// Level 6 (Foxie's Place)
#define LEVEL_7 0x06	// Level 7 (Dark Jungle)
#define LEVEL_8 0x07	// Level 8 (Clocktower)
#define LEVEL_9 0x08	// Level 9 (Prehistoric Jungle)
#define LEVEL_A 0x09	// Level A (Volcanic Planet)
#define LEVEL_B 0x0A	// Level B (Icy Planet)
#define LEVEL_C 0x0B	// Level C (Huge Castle [FINAL])
#define LEVEL_D 0x0C	// Level D (Hidden Galaxy Level)
// Total Levels: 13


// B and A buttons
#define BTN_A PAD_A
#define BTN_B PAD_B

// Dpad keys
#define DPD_U PAD_UP
#define DPD_D PAD_DOWN
#define DPD_L PAD_LEFT
#define DPD_R PAD_RIGHT

// Start/Select buttons
#define BTN_ST PAD_START
#define BTN_SL PAD_SELECT

#include "platformer.h"			// Platformer Engine
#include "platformer.c"			// Function defs.

// Screen attribute table size
#define ATTR_SIZE 0x40

// Make sure to put tileset into CHR ROM

//#resource "tset.chr"
//#link "tset.s"

/// Link audio stuff

//#link "famitone2.s"
//#link "sfx.s"
//#link "music.s"


const char PALETTE_0[] =
{
  0x0f,
  
  0x01,0x11,0x21, 0x0,
  0x00,0x10,0x30, 0x0,
  0x0a,0x1a,0x2a, 0x0,
  0x04,0x14,0x24, 0x0,
  
  0x01,0x11,0x21, 0x0,
  0x00,0x00,0x00, 0x0,
  0x00,0x00,0x00, 0x0,
  0x00,0x00,0x00, 0x0
};
const char PALETTE_1[] =
{
  0x0f,
  
  0x07,0x17,0x27, 0x0,
  0x09,0x19,0x29, 0x0,
  0x00,0x10,0x20, 0x0,
  0x00,0x10,0x20, 0x0,
  
  0x01,0x11,0x21, 0x0,
  0x02,0x12,0x22, 0x0,
  0x00,0x00,0x00, 0x0,
  0x00,0x00,0x00, 0x0
};
const char PALETTE_LVLSEL[] =
{
  0x0f,
  
  0x04,0x14,0x24, 0x0,
  0x01,0x11,0x21, 0x0,
  0x09,0x19,0x29, 0x0,
  0x00,0x00,0x11, 0x0,
  
  0x00,0x00,0x30, 0x0,
  0x00,0x00,0x00, 0x0,
  0x00,0x00,0x00, 0x0,
  0x00,0x00,0x00, 0x0
};
const char PLPAL_0[] = { 0x0f,0x01,0x11,0x21, 0x0 };
const char PLPAL_1[] = { 0x0f,0x04,0x14,0x24, 0x0 };
const char PLPAL_2[] = { 0x0f,0x06,0x16,0x26, 0x0 };
const char PLPAL_3[] = { 0x0f,0x07,0x17,0x27, 0x0 };
const char PLPAL_4[] = { 0x0f,0x08,0x18,0x28, 0x0 };
const char PLPAL_5[] = { 0x0f,0x0a,0x1a,0x2a, 0x0 };

static unsigned char wait = 160;
static unsigned char frame_cnt = 0;

#pragma data-name(push, "ZEROPAGE")
#pragma bss-name(push, "ZEROPAGE")

void fade_in()
{
  byte vb;
  for(vb=0; vb<=4; vb++)
  {
    pal_bright(vb);
    
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
  }
}
void fade_out()
{
  byte vb = 4;
  byte i;
  for(i=4; i>0; i--)
  {
    vb--;
    pal_bright(vb);
    
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
    ppu_wait_frame();
  }
}
void title_blink(const byte wait_time)
{
  if(wait)
  {
    wait--;
  }
  else
  {
    pal_col(7,(frame_cnt&32)?0x0f:0x30);
    frame_cnt++;
    wait = wait_time;
  }
}
void level1()
{
  fade_out();
  
  ppu_off();
  
  pal_bg(PALETTE_1);
  
  set_vram_buffer();
  clear_vram_buffer();
  load_room();
  
  ppu_on_all();
  fade_in();
}
void lvlselect()
{
  fade_out();
  
  ppu_off();
  
  pal_all(PALETTE_LVLSEL);
  
  vram_adr(NAMETABLE_A);
  vram_unrle(NAMT_LEVELSELECT);
  
  vram_adr(0x23c0);
  vram_write(ATTR_LEVELSELECT, ATTR_SIZE);
  
  ppu_on_all();
  
  fade_in();
}
void draw_player(const char* spr, const byte x, const byte y)
{ oam_meta_spr(x, y, 0, spr); }
void change_color(const byte color)
{
  if(color == 0x00)pal_spr(PLPAL_0);
  if(color == 0x01)pal_spr(PLPAL_1);
  if(color == 0x02)pal_spr(PLPAL_2);
  if(color == 0x03)pal_spr(PLPAL_3);
  if(color == 0x04)pal_spr(PLPAL_4);
  if(color == 0x05)pal_spr(PLPAL_5);
}
extern char bloboo_music_data[];
extern char sound_data[];

void main(void)
{
  // Declare variables here
  byte state = TITLE;
  byte level = LEVEL_1;
  byte color = 0x00;
  
  byte tl = 500;
  byte tm = 0;
  bool bf = false;
  bool sp = true;
  
  byte key = 0;
  
  int arr_x = 80;
  int arr_y = 120;
  
  bool paused = false;
  
  famitone_init(bloboo_music_data);
  sfx_init(sound_data);
  nmi_set_callback(famitone_update);
  // Turn PPU off
  ppu_off();
  
  // Clear OAM buffer
  oam_clear();
  
  // Palette data
  pal_bright(0);		// Palette Brightness
  pal_bg(PALETTE_0);		// Background Palette Def
  pal_spr(PLPAL_0);
  
  bank_spr(1);			// Set sprite table to table 2
  
  // Draw title screen
  vram_adr(NAMETABLE_A);	// Set address to Nam. A
  vram_unrle(NAMT_TITLE);	// Unpack namtable into VRAM
  
  vram_adr(0x23c0);	// Set to attribute table address
  
  // Write to attribute table
  vram_write(ATTR_TITLE, ATTR_SIZE);
  
  set_vram_buffer();
  clear_vram_buffer();
  
  ppu_on_all();			// Turn PPU on
  fade_in();			// Fade in
  
  music_play(0);
  
  /* GAME LOOP */
  while(1)
  {
    pad_t = pad_trigger(0);
    pad = pad_state(0);
    if(state == TITLE)
    {
      title_blink(50);
      if(pad_t & BTN_ST)
      {
        sfx_play(SFX_SELECT_YES,0);
        music_stop();
        bf = true;
      }
      if(pad & BTN_ST && key <= 6)tl-=0;
      if(bf)
      {
        title_blink(5);
        tl--;
        if(tl == 0) { tl = 500; tm++; };
        if(tm == 5)
        {
          if(key <= 6) { level1(); state = GAME; }
          if(key >= 7) { lvlselect(); state = LVLSELECT; }
        }
      }
      if(pad & DPD_L && key == 0)key++;
      if(pad & DPD_R && key == 1)key++;
      if(pad & DPD_L && key == 2)key++;
      if(pad & BTN_SL && key == 3)key++;
      if(pad & BTN_A && key == 4)key++;
      if(pad & BTN_B && key == 5)key++;
      if(pad & BTN_A && key == 6)key++;
      if(key == 7 && sp) { sfx_play(COMBO_ACCEPT, 0); sp=false; }
    }
    if(state == GAME && level == LEVEL_1)
    {
      ppu_wait_nmi();
      if(!paused)
      {
        color_emphasis(COL_EMP_NORMAL);
        
        pad_t = pad_trigger(0);
        pad = pad_state(0);
        
        clear_vram_buffer();
        
        input();
        //check_spr_objects();
        //sprite_collisions();
        //enemy_moves();
        
        set_scroll_x(scroll_x);
        set_scroll_y(scroll_y);
        
        if(is_walking && collision_D)plyr_walk();
        else
        {
          wlk_wait = 15;
          cur_spr_L = BLB_L;
          cur_spr_R = BLB_R;
        }
        draw_screen_R();
        draw_sprites(false);
      }
      else
      {
        color_emphasis(COL_EMP_DARK);
        draw_sprites(true);
      }
      if(pad_t & BTN_ST)paused = !paused;
      if(pad & BTN_ST)paused = paused;
    }
    if(state == LVLSELECT)
    {
      if(pad_t & DPD_D && arr_y < 216) { arr_y+=8; sfx_play(SFX_SELECT, 0); }
      if(pad_t & DPD_D && arr_y >= 216)arr_y = 120;
      if(pad & DPD_D)arr_y+=0;
      if(pad_t & DPD_U && arr_y > 112) { arr_y-=8; sfx_play(SFX_SELECT, 0); }
      if(pad_t & DPD_U && arr_y <= 112)arr_y = 208;
      if(pad & DPD_U)arr_y+=0;
      oam_spr(arr_x-1, arr_y - 1, 0x2c, 0, 0);
    }
  }
}

/* END OF FILE */
