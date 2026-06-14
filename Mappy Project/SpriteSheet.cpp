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
	maxFrame = 16;
	curFrame = 0;
	//jumpFrame = 8;
	//jumpFrameDelay = 6;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 333;
	frameHeight = 499;
	animationColumns = 4;
	animationDirection = 0;

	image = al_load_bitmap("man_walking.png");
	al_convert_mask_to_alpha(image, al_map_rgb(254, 254, 254));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if (dir == 3) { //right key
		//curFrame = 12;
		animationDirection = 3;
		goingLeft = false;
		x += 2;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame >= maxFrame)
				curFrame = 12;
		}
	}
	else if (dir == 2) { //left key
		//curFrame = 8;
		animationDirection = 2;
		goingLeft = true;
		x -= 2;
		if (++frameCount >= frameDelay)
		{
			frameCount = 0;
			if (++curFrame >= 12)
				curFrame = 8;
		}

	}
	else if (dir==1) {//up key
		//curFrame = 4;
		animationDirection = 1;
		y -= 2;
		if (++frameCount >= frameDelay)
		{
			frameCount = 0;
			if (++curFrame >= 8)
				curFrame = 4;
		}
	}
	
	else if (dir == 0) {//down key
		//curFrame = 0;
		animationDirection = 0;
		y += 2;
		if (++frameCount >= frameDelay)
		{
			frameCount = 0;
			if (++curFrame >= 4)
				curFrame = 0;
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
	if (animationDirection == 2)
	{
		if (collided(x, y+charWidth/2)) { //collision detection to the left
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 3)
	{
		if (collided(x+charWidth+2, y) || collided(x+charWidth+2, y+charHeight)) { //collision detection to the right
			x = oldx;
			y = oldy;
		}
	}

	if (animationDirection == 1)
	{
		if (collided(x, y) || collided(x+charWidth, y)) { //collision detection up
			x = oldx;
			y = oldy;
		}

	}
	if (animationDirection == 0) {
		if (collided(x, y +charHeight) || collided(x+charWidth, y+charHeight)) {
			x = oldx;
			y = oldy;
		}
	}
	//collision detection down?
	
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
	int fy = animationDirection * frameHeight;

	float minimizeX = (float)newWidth / charWidth;
	float minimizeY = (float)newHeight / charHeight;

	if (animationDirection == 5) {
		al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 0, frameWidth, frameHeight, al_map_rgb(255, 255, 255), 0, 0, x - xoffset, y - yoffset, (48.0f / 333.0f), (72.0f / 499.0f), 0, 0);
	}
	else {
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, al_map_rgb(255, 255, 255), 0, 0, x - xoffset, y - yoffset, (48.0f / 333.0f), (72.0f / 499.0f), 0, 0);
	}
}