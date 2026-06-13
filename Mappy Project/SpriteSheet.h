#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
//Lucia Donley
using namespace std;
class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);
	friend int collideWithCeiling(int x, int y);
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawSprites(int xoffset, int yoffset);
	bool CollideSprite();
	float getX() { return x; }
	float getY() { return y; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	//int jumping(int jump, const int JUMPIT);
	bool CollisionEndBlock();

private:
	float x;
	float y;

	int maxFrame;
	int curFrame;
	//int jumpFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;
	int charWidth;
	int charHeight;
	//bool isJumping;
	bool goingLeft;
	//int jumpFrameDelay;
	ALLEGRO_BITMAP* image;
};