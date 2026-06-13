#include "SpriteSheet.h"
//Lucia Donley

Sprite::Sprite()
{
	image = NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitSprites(int width, int height)
{
	x = 120;
	y = 60;

	//need to check if dir == something for jumping
	//maxFrame = 12
	//new if statement in draw function for jumping
	maxFrame = 4;
	curFrame = 0;
	//jumpFrame = 8;
	//jumpFrameDelay = 6;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 333;
	frameHeight = 499;
	animationColumns = 4;
	animationDirection = 1;

	image = al_load_bitmap("man_walking.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if (dir == 1) { //right key
		animationDirection = 1;
		goingLeft = false;
		x += 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
			//if (++curFrame >= maxFrame)
			//	curFrame = 0;
		}
	}
	else if (dir == 0) { //left key
		animationDirection = 0;
		goingLeft = true;
		x -= 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}

	}
	else if (dir==3) {//up key
		animationDirection = 3;
		y -= 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
	
	else if (dir == 4) {//down key
		animationDirection = 4;
		y += 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}

	else { //represent that they hit the space bar and that mean direction = 0
		goingLeft = false;
		animationDirection = dir;
		//isJumping = false;
	}

	charWidth = 48;
	charHeight = 72;

	//check for collided with foreground tiles
	if (animationDirection == 0)
	{
		if (collided(x, y + charHeight)) { //collision detection to the left
			x = oldx;
			y = oldy;
		}

	}
	else if (animationDirection == 1)
	{
		if (collided(x + charWidth, y + charHeight)) { //collision detection to the right
			x = oldx;
			y = oldy;
		}
	}

	if (animationDirection == 3)
	{
		if (collided(x, y - charHeight)) { //collision detection up
			x = oldx;
			y = oldy;
		}

	}
	
}

bool Sprite::CollisionEndBlock()
{

	if (endValue(x + charWidth / 2, y + charHeight + 5))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{

	float newWidth = 48.0f;
	float newHeight = 72.0f;
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	float minimizeX = (float)newWidth / charWidth;
	float minimizeY = (float)newHeight / charHeight;

	//int jumpx = (jumpFrame % animationColumns) * frameWidth;
	//int jumpy = (jumpFrame / animationColumns) * frameHeight;

	if (animationDirection == 1) {
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, al_map_rgb(255, 255, 255), 0, 0, x - xoffset, y - yoffset, (48.0f / 333.0f), (72.0f / 499.0f), 0, 0);
	}
	else if (animationDirection == 0) {
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, al_map_rgb(255, 255, 255), 0, 0, x - xoffset, y - yoffset, (48.0f / 333.0f), (72.0f / 499.0f), 0, ALLEGRO_FLIP_HORIZONTAL);
	}
	else if (animationDirection == 2) {
		al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 0, frameWidth, frameHeight, al_map_rgb(255, 255, 255), 0, 0, x - xoffset, y - yoffset, (48.0f / 333.0f), (72.0f / 499.0f), 0, 0);
	}
	else {
		al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 0, frameWidth, frameHeight, al_map_rgb(255, 255, 255), 0, 0, x - xoffset, y - yoffset, (48.0f / 333.0f), (72.0f / 499.0f), 0, 0);
	}
}