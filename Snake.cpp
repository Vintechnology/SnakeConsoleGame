#include "Snake.h"
#include "Position.h"
#include "ScreenBuffer.h"


namespace Snake {
	Position snakeBody[100];
	int length;
	int head;
	bool death;

	void initSnake(int x, int y)
	{
		length = 1;
		int head = 0;
		death = false;

		snakeBody[head].x = x;
		snakeBody[head].y = y;
	}

	void updateSnake() 
	{
		for (int i = length - 1; i > 0; i--) {
			snakeBody[i] = snakeBody[i - 1];
		}
	}

	void grow()
	{
		if (length == 99) {
			die();
			return;
		}
		length++;
	}
	void move(int x, int y)
	{
		if (snakeBody[head].x == x && snakeBody[head].y == y)
			return;
		updateSnake();
		snakeBody[head].x = x;
		snakeBody[head].y = y;
	}
	void drawSnake()
	{
		for (int i = 0; i < length; i++)
			ScreenBuffer::drawToBuffer(snakeBody[i].x, snakeBody[i].y, '0');
	}
	bool isDead()
	{
		return death;
	}
	void die()
	{
		death = true;
	}

}