/* Platformer Engine Function Definition */

#define VRAMBUF ((byte*)0x700)

void load_room(void)
{
  set_data_pointer(Rooms[0]);
  set_mt_pointer(metatiles_lvl1);
  for(y = 0; ; y += 0x20)
  {
    for(x = 0; ; x += 0x20)
    {
      clear_vram_buffer();
      address = get_ppu_addr(0, x, y);
      index = (y & 0xf0) + (x >> 4);
      buffer_4_mt(address, index);
      flush_vram_update(VRAMBUF);
      if(x == 0xe0)break;
    }
    if(y == 0xe0)break;
  }
  
  set_data_pointer(Rooms[1]);
  for(y = 0; ; y += 0x20)
  {
    x = 0;
    clear_vram_buffer();
    address = get_ppu_addr(1, x, y);
    index = (y & 0xf0);
    buffer_4_mt(address, index);
    flush_vram_update(VRAMBUF);
    if(y == 0xe0)break;
  }
  clear_vram_buffer();
  
  memcpy(c_map, Cols[0], 240);
}

void draw_sprites(void)
{
  oam_clear();
  
  sprid = 0;
  
  set_sprite_zero();
  if(direction == LEFT)
  {
    sprid = oam_meta_spr(high_byte(Bloboo.x), high_byte(Bloboo.y), sprid, cur_spr_L);
  }
  else
  {
    sprid = oam_meta_spr(high_byte(Bloboo.x), high_byte(Bloboo.y), sprid, cur_spr_R);
  }
  
  // Draw enemies and stuff when ready
}

void movement(void)
{
  old_x = Bloboo.x;
	
	if(pad & DPD_L){
		direction = LEFT;
		if(Bloboo.x <= 0x100) {
			Bloboo.vel_x = 0;
			Bloboo.x = 0x100;
		}
		else if(Bloboo.x < 0x400) { // don't want to wrap around to the other side
			Bloboo.vel_x = -0x100;
		}
		else {
			Bloboo.vel_x -= ACCEL;
			if(Bloboo.vel_x < -MAX_SPEED)Bloboo.vel_x = -MAX_SPEED;
		}
          	is_walking = true;
	}
	else if (pad & DPD_R){
		
		direction = RIGHT;

		Bloboo.vel_x += ACCEL;
		if(Bloboo.vel_x > MAX_SPEED)Bloboo.vel_x = MAX_SPEED;
        	is_walking = true;
        }
	else { // nothing pressed
		if(Bloboo.vel_x >= 0x100)Bloboo.vel_x -= ACCEL;
		else if(Bloboo.vel_x < -0x100)Bloboo.vel_x += ACCEL;
		else Bloboo.vel_x = 0;
        	is_walking = false;
	}
	
	Bloboo.x += Bloboo.vel_x;
	
	if(Bloboo.x > 0xf800) { // make sure no wrap around to the other side
		Bloboo.x = 0x100;
		Bloboo.vel_x = 0;
	} 
	
	L_R_switch = 1; // shinks the y values in bg_coll, less problems with head / feet collisions
	
	Generic.x = high_byte(Bloboo.x); // this is much faster than passing a pointer to BoxGuy1
	Generic.y = high_byte(Bloboo.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	bg_collision();
	if(collision_R && collision_L){ // if both true, probably half stuck in a wall
		Bloboo.x = old_x;
		Bloboo.vel_x = 0;
	}
	else if(collision_L) {
		Bloboo.vel_x = 0;
		high_byte(Bloboo.x) = high_byte(Bloboo.x) - eject_L;
		
	}
	else if(collision_R) {
		Bloboo.vel_x = 0;
		high_byte(Bloboo.x) = high_byte(Bloboo.x) - eject_R;
	} 


	
// handle y

// gravity

	// BoxGuy1.vel_y is signed
	if(Bloboo.vel_y < 0x300){
		Bloboo.vel_y += GRAVITY;
	}
	else{
		Bloboo.vel_y = 0x300; // consistent
	}
	Bloboo.y += Bloboo.vel_y;
	
	L_R_switch = 0;
	Generic.x = high_byte(Bloboo.x); // the rest should be the same
	Generic.y = high_byte(Bloboo.y);
	bg_collision();
	
	if(collision_U) {
		high_byte(Bloboo.y) = high_byte(Bloboo.y) - eject_U;
		Bloboo.vel_y = 0;
	}
	else if(collision_D) {
		high_byte(Bloboo.y) = high_byte(Bloboo.y) - eject_D;
		Bloboo.y &= 0xff00;
		if(Bloboo.vel_y > 0) {
			Bloboo.vel_y = 0;
		}
	}


	// check collision down a little lower than hero
	Generic.y = high_byte(Bloboo.y); // the rest should be the same
	bg_check_low();
	if(collision_D) {
		if(pad_t & PAD_A) {
			Bloboo.vel_y = JUMP_VEL; // JUMP
		}
		
	}
	
	// do we need to load a new collision map? (scrolled into a new room)
	if((scroll_x & 0xff) < 4){
		new_cmap();
	}
	
// scroll
	temp5 = Bloboo.x;
	if (Bloboo.x > MAX_RIGHT){
		temp1 = (Bloboo.x - MAX_RIGHT) >> 8;
		scroll_x += temp1;
		high_byte(Bloboo.x) = high_byte(Bloboo.x) - temp1;
	}

	if(scroll_x >= MAX_SCROLL) {
		scroll_x = MAX_SCROLL; // stop scrolling right, end of level
		Bloboo.x = temp5; // but allow the x position to go all the way right
		if(high_byte(Bloboo.x) >= 0xf1) {
			Bloboo.x = 0xf100;
		}
	}
}

//void enemy_moves(void);

void bg_collision(void)
{
  // note, uses bits in the metatile data to determine collision
	// sprite collision with backgrounds
	// load the object's x,y,width,height to Generic, then call this
	

	collision_L = 0;
	collision_R = 0;
	collision_U = 0;
	collision_D = 0;
	
	if(Generic.y >= 0xf0) return;
	
	temp6 = temp5 = Generic.x + scroll_x; // upper left (temp6 = save for reuse)
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8; // high byte x
	
	eject_L = temp1 | 0xf0;
	
	temp3 = Generic.y; // y top
	
	eject_U = temp3 | 0xf0;
	
	if(L_R_switch) temp3 += 2; // fix bug, walking through walls
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ // find a corner in the collision map
		++collision_L;
		++collision_U;
	}
	
	// upper right
	temp5 += Generic.width;
	temp1 = temp5 & 0xff; // low byte x
	temp2 = temp5 >> 8; // high byte x
	
	eject_R = (temp1 + 1) & 0x0f;
	
	// temp3 is unchanged
	bg_collision_sub();
	
	if(collision & COL_ALL){ // find a corner in the collision map
		++collision_R;
		++collision_U;
	}
	
	
	// again, lower
	
	// bottom right, x hasn't changed
	
	temp3 = Generic.y + Generic.height; //y bottom
	if(L_R_switch) temp3 -= 2; // fix bug, walking through walls
	eject_D = (temp3 + 1) & 0x0f;
	if(temp3 >= 0xf0) return;
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ // find a corner in the collision map
		++collision_R;
	}
	if(collision & (COL_DOWN|COL_ALL)){ // find a corner in the collision map
		++collision_D;
	}
	
	// bottom left
	temp1 = temp6 & 0xff; // low byte x
	temp2 = temp6 >> 8; // high byte x
	
	//temp3, y is unchanged

	bg_collision_sub();
	
	if(collision & COL_ALL){ // find a corner in the collision map
		++collision_L;
	}
	if(collision & (COL_DOWN|COL_ALL)){ // find a corner in the collision map
		++collision_D;
	}

	if((temp3 & 0x0f) > 3) collision_D = 0; // for platforms, only collide with the top 3 pixels

}

void bg_collision_sub(void)
{
  coordinates = (temp1 >> 4) + (temp3 & 0xf0);
  
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

void draw_screen_R(void)
{
  pseudo_scroll_x = scroll_x + 0x120;
  
  temp1 = pseudo_scroll_x >> 8;
  
  set_data_pointer(Rooms[temp1]);
  nt = temp1 & 1;
  x = pseudo_scroll_x & 0xff;
  
  switch(scroll_count)
  {
    case 0:
      address = get_ppu_addr(nt, x, 0);
      index = 0 + (x >> 4);
      buffer_4_mt(address, index);
      
      address = get_ppu_addr(nt, x, 0x20);
      index = 0x20 + (x >> 4);
      buffer_4_mt(address, index);
      break;
      
    case 1:
      address = get_ppu_addr(nt, x, 0x40);
      index = 0x40 + (x >> 4);
      buffer_4_mt(address, index);
      
      address = get_ppu_addr(nt, x, 0x60);
      index = 0x60 + (x >> 4);
      buffer_4_mt(address, index);
      break;
      
    case 2:
      address = get_ppu_addr(nt, x, 0x80);
      index = 0x80 + (x >> 4);
      buffer_4_mt(address, index);
      
      address = get_ppu_addr(nt, x, 0xa0);
      index = 0xa0 + (x >> 4);
      buffer_4_mt(address, index);
      break;
    
    default:
      address = get_ppu_addr(nt, x, 0xc0);
      index = 0xc0 + (x >> 4);
      buffer_4_mt(address, index);
      
      address = get_ppu_addr(nt, x, 0xe0);
      index = 0xe0 + (x >> 4);
      buffer_4_mt(address, index);
      break;
  }
  
  scroll_count++;
  scroll_count &= 3;
}

void new_cmap(void)
{
  room = ((scroll_x >> 8) + 1);
  
  map = room & 1;
  if(!map)
  {
    memcpy(c_map, Cols[room], 240);
  }
  else
  {
    memcpy(c_map2, Cols[room], 240);
  }
}

void bg_check_low(void)
{
  // floor collisions
	collision_D = 0;
	
	temp5 = Generic.x + scroll_x;    //left
	temp1 = temp5 & 0xff; //low byte
	temp2 = temp5 >> 8; //high byte
	
	temp3 = Generic.y + Generic.height + 1; // bottom
	
	if(temp3 >= 0xf0) return;
	
	bg_collision_sub();
	
	if(collision & (COL_DOWN|COL_ALL)){ // find a corner in the collision map
		++collision_D;
	}
	
	
	//temp5 = right
	temp5 += Generic.width;
	temp1 = temp5 & 0xff; //low byte
	temp2 = temp5 >> 8; //high byte
	
	//temp3 is unchanged
	bg_collision_sub();
	
	if(collision & (COL_DOWN|COL_ALL)){ // find a corner in the collision map
		++collision_D;
	}
	
	if((temp3 & 0x0f) > 3) collision_D = 0; // for platforms, only collide with the top 3 pixels

}

//void sprite_collisions(void);

//void check_spr_object(void);

char get_position(void)
{
  temp5 -= scroll_x;
  temp_x = temp5 & 0xff;
  if(high_byte(temp5))return 0;
  return 1;
}

//void spr_obj_init(void);


void set_sprite_zero(void)
{
  oam_spr(1, 24, 0xff, 0, 3);
}