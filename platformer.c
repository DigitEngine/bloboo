/* Platformer Engine Function Definition */

#define VRAMBUF ((byte*)0x700)

void load_room(void)
{
  set_data_pointer(Rooms[0]);
  memcpy(c_map, Rooms[0], 240);
  sprite_obj_init();
}

void draw_sprites(void)
{
  oam_clear();
  
  sprid = 0;
  
  if(direction == LEFT)
  {
    sprid = oam_meta_spr(high_byte(Bloboo.x), high_byte(Bloboo.y), sprid, PLYR_L);
  }
  else
  {
    sprid = oam_meta_spr(high_byte(Bloboo.x), high_byte(Bloboo.y), sprid, PLYR_R);
  }
  
  // Draw enemies and stuff when ready
}

void movement(void)
{
  old_x = Bloboo.x;
  if(pad & DPD_L)
  {
    direction = LEFT;
    if(Bloboo.x <= 0x100)
    {
      Bloboo.vel_x = 0;
      Bloboo.x = 0x100;
    }
    else if(Bloboo.x < 0x400)
    {
      Bloboo.vel_x = -0x100;
    }
    else
    {
      Bloboo.vel_x -= ACCEL;
      if(Bloboo.vel_x < -MAX_SPEED)Bloboo.vel_x = -MAX_SPEED;
    }
  }
  else if(pad & DPD_R)
  {
    direction = RIGHT;
    
    Bloboo.vel_x += ACCEL;
    if(Bloboo.vel_x > MAX_SPEED)Bloboo.vel_x = MAX_SPEED;
  }
  else
  {
    if(Bloboo.vel_x >= 0x100)Bloboo.vel_x -= MAX_SPEED;
    else if(Bloboo.vel_x > -0x100)Bloboo.vel_x += MAX_SPEED;
    else Bloboo.vel_x = 0;
  }
  
  Bloboo.x += Bloboo.vel_x;
  
  if(Bloboo.x > 0xf800)
  {
    Bloboo.x = 0x100;
    Bloboo.vel_x = 0;
  }
  
  L_R_switch = 1;
  
  Generic.x = high_byte(Bloboo.x);
  Generic.y = high_byte(Bloboo.y);
  Generic.width = HERO_WIDTH;
  Generic.height = HERO_HEIGHT;
  bg_collision();
  if(collision_R && collision_L)
  {
    Bloboo.x = old_x;
    Bloboo.vel_x = 0;
  }
  else if(collision_L)
  {
    Bloboo.vel_x = 0;
    high_byte(Bloboo.x) = high_byte(Bloboo.x) - eject_L;
  }
  else if(collision_R)
  {
    Bloboo.vel_x = 0;
    high_byte(Bloboo.x) = high_byte(Bloboo.x) - eject_R;
  }
  
  if(Bloboo.vel_y < 0x300)
  {
    Bloboo.vel_y += GRAVITY;
  }
  else
  {
    Bloboo.vel_y = 0x300;
  }
  
  Bloboo.y += Bloboo.vel_y;
  
  L_R_switch = 0;
  Generic.x = high_byte(Bloboo.x);
  Generic.y = high_byte(Bloboo.y);
  bg_collision();
  
  if(collision_U)
  {
    high_byte
  }
}