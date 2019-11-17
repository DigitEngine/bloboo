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
    high_byte(Bloboo.y) = high_byte(Bloboo.y) - eject_U;
    Bloboo.vel_y = 0;
  }
  else if(collision_D)
  {
    high_byte(Bloboo.y) = high_byte(Bloboo.y) - eject_D;
    Bloboo.vel_y = 0;
  }
  
  Generic.y = high_byte(Bloboo.y);
  bg_check_low();
  if(collision_D)
  {
    if(pad_t & BTN_A)Bloboo.vel_y = JUMP_VEL;
    // Remember to play jump sound effect
  }
  
  if((scroll_x & 0xff) < 4)
  {
    new_cmap();
  }
  
  temp5 = Bloboo.x;
  if(Bloboo.x > MAX_RIGHT)
  {
    temp1 = (Bloboo.x - MAX_RIGHT) >> 8;
    scroll_x += temp1;
    high_byte(Bloboo.x) = high_byte(Bloboo.x) - temp1;
  }
  if(scroll_x > MAX_SCROLL)
  {
    scroll_x = MAX_SCROLL;
    Bloboo.x = temp5;
    if(high_byte(Bloboo.x) >= 0xf1)
    {
      Bloboo.x = 0xf100;
    }
  }
}

//void enemy_moves(void);

void bg_collision(void)
{
  collision_L = 0;
  collision_R = 0;
  collision_U = 0;
  collision_D = 0;
  
  if(Generic.y = 0xf0)return;
  
  temp6 = temp5 = Generic.x + scroll_x;
  temp1 = temp5 & 0xff;
  temp2 = temp5 >> 8;
  
  eject_L = temp1 | 0xf0;
  
  temp3 = Generic.y;
  
  eject_U = temp3 | 0xf0;
  
  if(L_R_switch) temp3 += 2;
  
  bg_collision_sub();
  
  if(collision & COL_ALL)
  {
    collision_L++;
    collision_U++;
  }
  
  temp5 += Generic.width;
  temp1 = temp5 & 0xff;
  temp2 = temp5 >> 8;
  
  eject_R = (temp1 + 1) & 0xff;
  
  bg_collision_sub();
  
  if(collision & COL_ALL)
  {
    collision_R++;
    collision_U++;
  }
  
  temp3 = Generic.y + Generic.height;
  if(L_R_switch)temp3 -= 2;
  eject_D = (temp3 + 1) & 0xff;
  if(temp3 >= 0xf0)return;
  
  bg_collision_sub();
  
  if(collision & COL_ALL)
  {
    collision_R++;
  }
  if(collision & (COL_DOWN|COL_ALL))
  {
    collision_D++;
  }
  
  temp1 = temp6 & 0xff;
  temp2 = temp6 >> 8;
  
  bg_collision_sub();
  
  if(collision & COL_ALL)
  {
    collision_L++;
  }
  if(collision & (COL_DOWN|COL_ALL))
  {
    collision_D++;
  }
  
  if((temp3 & 0x0f) > 3)collision_D = 0;
}

void bg_collision_sub(void)
{
  coordinates = (temp1 >> 4) + (temp3 * 0xf0);
  
  map = temp2&1;
  if(!map)
  {
    collision = c_map[coordinates];
  }
  else
  {
    collision = c_map2[coordinates];
  }
  collision = is_solid[collision];
}