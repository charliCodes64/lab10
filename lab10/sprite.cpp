#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"
#include <iostream>

using namespace std; 
 
void sprite::drawSprite()
{
 		if (effect == 0) {//spin
			rotate += 0.4;
			al_draw_rotated_bitmap(image[curframe], width / 2, height / 2, x + (width / 2), y + (height / 2), rotate, 0);
			al_convert_mask_to_alpha(image[curframe], al_map_rgb(255, 255, 255));
		}
 		else if (effect == 1) {//scared
			al_draw_tinted_bitmap(image[curframe], color, x, y, 0);
			al_convert_mask_to_alpha(image[curframe], al_map_rgb(255, 255, 255));
		}
		else if (effect == 2) {//shrink
			if (visable) {
				al_draw_scaled_bitmap(image[curframe], 0, 0, width, height, x, y, width * scale, height * scale, 0);
				al_convert_mask_to_alpha(image[curframe], al_map_rgb(255, 255, 255));
			}
		}
		else if (effect == 3) {//freeze
			if (freeze > 0) {
				al_draw_tinted_bitmap(image[curframe], al_map_rgb(135, 135, 0), x, y, 0);  
				al_convert_mask_to_alpha(image[curframe], al_map_rgb(255, 255, 255));
			}
			else {
				al_draw_bitmap(image[curframe], x, y, 0);
				al_convert_mask_to_alpha(image[curframe], al_map_rgb(255, 255, 255));
			}
		}
		else {//no change
			al_draw_bitmap(image[curframe], x, y, 0);
			al_convert_mask_to_alpha(image[curframe], al_map_rgb(255, 255, 255));
	}
}

	void sprite::updatesprite()
	{
		if (freeze > 0) {//keeps frozen on x and y until timer is up
			x = freezeX;
			y = freezeY;
			freeze--;
		}

		//update x position
		if (++xcount > xdelay)
		{
			xcount = 0;
			x += xspeed;
		}

		//update y position
		if (++ycount > ydelay)
		{
			ycount = 0;
			y += yspeed;
		}


		if (framecount++ > framedelay)
		{
			framecount = 0;
			curframe++;
			if (curframe >= maxframe)
				curframe = 0;
		}
	}

	void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
	{
		//simple screen bouncing behavior
		if (x < 0)
		{
			x = 0;
			xspeed = rand() % 2 + 4;
			animdir *= -1;
		}

		else if (x > SCREEN_W - width)
		{
			x = SCREEN_W - width;
			xspeed = rand() % 2 - 6;
			animdir *= -1;
		}

		if (y < 0)
		{
			y = 0;
			yspeed = rand() % 2 + 4;
			animdir *= -1;
		}

		else if (y > SCREEN_H - height)
		{
			y = SCREEN_H - height;
			yspeed = rand() % 2 - 6;
			animdir *= -1;
		}
	}
	void sprite::load_animated_sprite(int size, int effectType)
	{
		effect = effectType;

		char s[80];
		maxframe = size;
		for (int n = 0; n < size; n++)
		{
			sprintf_s(s, "Alien%d.bmp", n);
			image[n] = al_load_bitmap(s);
			//al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
		}
		width = al_get_bitmap_width(image[0]);
		height = al_get_bitmap_height(image[0]);
		curframe = 0;
		framedelay = 5;
		framecount = 0;
	}

	void sprite::collision(sprite sprites[], int size, int comp, int WIDTH, int HEIGHT) {
		for (int i = 0; i < size; ++i) {
			if (scale <= 0.5f) {//setting visable to false when to small
				visable = false;
				std::cout << "Sprite is to small";

			}
			if (visable == false || freeze > 0){//ignoring frozen sprite when its frozen so it want teleport again
				return;
			}
			if (i == comp) {
				return;
			}
			else {
				int randX = sprites[i].getX();//used for other sprites borders
				int randY = sprites[i].getY();

				bool posX = (x >= randX - width) && (x <= randX + width);//overlap checking of x
				bool posY = (y >= randY - height) && (y <= randY + height);

				//checking if this sprite overlaps with the other sprites 
				if (posX && posY) {
					if (effect == 1) { //scared
						color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
					}
					else if (effect == 2) { //shrank
						scale *= 0.9f;
					}
					else if (effect == 3) { //freeze
						freeze = 300;// 5 second freeze 300/60 = 5
						freezeX = x;
						freezeY = y;
					}
					x = rand() % WIDTH;//teleport after any collision
					y = rand() % HEIGHT;
				}
			}
		}
	}

	sprite::~sprite()
	{
		for (int i = 0; i < maxframe; i++) {
			al_destroy_bitmap(image[i]);
			//al_convert_mask_to_alpha(image[i], al_map_rgb(255, 255, 255));
		}
 	}
