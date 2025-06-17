#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include "Sprite.h"
#include <iostream>
using namespace std;
//Charlton Infinger
int main(void)
{
	//variables
	int width = 800;
	int height = 600;
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	sprite image[5];


	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT* font24 = al_load_font("GoldenAge.ttf", 16, 0);
	if (!font24) {
		al_show_native_message_box(NULL, NULL, "Error", "Can not load GoldenAge.ttf", NULL, 0);
	}
	/*if (!font24) {
		std::cout << "Font is not found!\n";
	}*/

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	al_install_keyboard();
	al_init_image_addon();
	timer = al_create_timer(1.0 / FPS);
	//sprite sprite;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);

	for (int i = 0; i < 5; i++) {
		image[i].load_animated_sprite(9, i);
	}
	//std::cout << "try5" << std::endl;

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			for (int i = 0; i < 5; i++) {//grabs all 5 to bounce
				image[i].bouncesprite(width, height);
			}
			for (int i = 0; i < 5; i++) {//sets collision for all 5
				image[i].collision(image, 5, i, width, height);
			}

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{

			al_clear_to_color(al_map_rgb(0, 0, 0));

			redraw = false;
			for (int i = 0; i < 5; i++) {//changing based on updates
				image[i].updatesprite();
			}
			for (int i = 0; i < 5; i++) {//drawing all 5
				image[i].drawSprite();
			}
			for (int i = 0; i < 5; i++) {//printing once shrinking sprint is to small
				if (!image[i].visable) {
					al_draw_text(font24, al_map_rgb(255, 80, 80), 10, 10, 0, "Sprite shrank out of existence!");
				}
			}
		/*	if (!sprite.alive) {
				std::cout << "Sprite is to small";  

				al_draw_text(font24, al_map_rgb(255, 80, 80), 10, 10, 0, "Shrank out of existence");
			}*/

			al_flip_display();
 		}
	}


	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}