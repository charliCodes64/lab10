#pragma once
class sprite
{
public:
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size, int effectType);
	void drawSprite();
	int getX() { return x; }
	int getY() { return y; }
	void collision(sprite sprites[], int size, int me, int WIDTH, int HEIGHT);
	float scale = 0.9f;
	int effect;
	bool visable = true; 



private:
	int x, y;
	int width, height;
	int xspeed, yspeed;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
 	float rotate = 0; 
  	int freezeX = 0, freezeY = 0;  
	int freeze = 0;  
 
 	ALLEGRO_BITMAP* image[9];
	ALLEGRO_COLOR color;

};