#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <iostream>
//Lucia Donley
using namespace std;

int collided(int x, int y);  //Tile Collision
int collideWithCeiling(int x, int y); //Collision with ceiling
bool endValue(int x, int y); //End Block with the User Value = 8
int main(void)
{
	bool hasWon = false;
	const int WIDTH = 900;
	const int HEIGHT = 480;
	bool keys[] = { false, false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//variables
	bool done = false;
	bool render = false;
	//Player Variable
	Sprite player;
	const int JUMPIT = 1600;
	int jump = JUMPIT;
	double current_seconds = 0;
	int not_double_secs = 0;
	bool timesUp = false;



	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* time_font = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	player.InitSprites(WIDTH, HEIGHT);

	int xOff = 0;
	int yOff = 0;
	if (MapLoad("sample.fmp", 1))
		return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	font = al_load_ttf_font("college.ttf", 54, 0);
	time_font = al_load_ttf_font("college.ttf", 36, 0);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	//draw the background tiles
	MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

	//draw foreground tiles
	MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
	player.DrawSprites(0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	while (!done)
	{
		current_seconds = al_get_time();
		not_double_secs = (int)current_seconds;

		

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			MapUpdateAnims();
			if (keys[UP])
				player.UpdateSprites(WIDTH, HEIGHT, 1);
			else if (keys[DOWN])
				player.UpdateSprites(WIDTH, HEIGHT, 0);
			else if (keys[LEFT])
				player.UpdateSprites(WIDTH, HEIGHT, 2);
			else if (keys[RIGHT])
				player.UpdateSprites(WIDTH, HEIGHT, 3);
			else if (keys[SPACE])
				;
			else
				player.UpdateSprites(WIDTH, HEIGHT, 5);
			
			render = true;

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
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				jump = 30;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//update the map scroll position
			xOff = player.getX() + player.getWidth() - WIDTH / 2;
			yOff = player.getY() + player.getHeight() - HEIGHT / 2;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0)
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT))
				yOff = mapheight * mapblockheight - HEIGHT;

			//draw the background tiles
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);

			//draw foreground tiles
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			//jump = player.jumping(jump, JUMPIT);
			player.DrawSprites(xOff, yOff);

			al_draw_textf(time_font, al_map_rgb(255, 0, 127), WIDTH - 250, HEIGHT - 35, 0, "Time Left: %d", 60 - not_double_secs);

			if (player.CollisionEndBlock()) {
				hasWon = true;
				al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, 150, 0, "Done in %d seconds!", not_double_secs);
			}
			else if (current_seconds >= 60.0) {
				timesUp = true;
				al_draw_textf(font, al_map_rgb(255, 0, 0), WIDTH / 2, 150, 0, "Time's Up!", not_double_secs);
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (hasWon) {
				break;
			}
			else if (timesUp) {
				break;
			}
		}
	}
	al_rest(7.0);
	MapFreeMem();
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}



int collided(int x, int y)
{
	if (x < 0 || y < 0 || x >= mapwidth * mapblockwidth || y >= mapheight * mapblockheight)
		return 0;

	BLKSTR* blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return (blockdata->tl || blockdata->tr);
}
int collideWithCeiling(int x, int y) {

	if (x < 0 || y < 0 || x >= mapwidth * mapblockwidth || y >= mapheight * mapblockheight)
		return 0;

	BLKSTR* blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return (blockdata->bl || blockdata->br);
}

bool endValue(int x, int y)
{

	BLKSTR* data;
	data = MapGetBlock(x / mapblockwidth, y / mapblockheight);

	//if( data->user1 == 8 )
	//{
	//	return true;
	//}
	if (data->user1 == 9) {
		return true;
	}
	else {
		return false;
	}
}