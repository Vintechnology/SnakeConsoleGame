#include "Game.h"
#include "ScreenBuffer.h"
#include "Snake.h"
#include <iostream>
#include <conio.h>
#include "Position.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int WIDTH = 100;
const int HEIGHT = 20;
bool gameOver;
int score;

enum Direction {
	STOP,
	UP,
	DOWN,
	LEFT,
	RIGHT
};


Position snakePos;
Direction snakeDirection;

Position fruitPos;

void SetUp() {
	gameOver = false;
	score = 0;

	
	snakePos.x = WIDTH / 2;
	snakePos.y = HEIGHT / 2;


	Snake::initSnake(snakePos.x, snakePos.y);

	fruitPos.x = std::rand() % (WIDTH - 2) + 1;
	fruitPos.y = std::rand() % (HEIGHT - 2) + 1;

	snakeDirection = Direction::STOP;
	ScreenBuffer::SetupBufferScreen(WIDTH, HEIGHT);
}

void Draw() {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x=0; x < WIDTH; x++) {
			if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) {
				ScreenBuffer::drawToBuffer(x, y, '#');
			}
			else if (x == fruitPos.x&&y == fruitPos.y) {
				ScreenBuffer::drawToBuffer(x, y, 'F');
			}
			else {
				ScreenBuffer::drawToBuffer(x, y, ' ');
			}
		}
	}

	Snake::drawSnake();
	ScreenBuffer::drawToConsole();
}

void Update() {
	Input();
	Logic();
	Draw();
}

void Input() {
	if (_kbhit()) {
		char keyPressed = _getch();
		switch (keyPressed)
		{
		case KEY_UP:
			snakeDirection = Direction::UP;
			break;
		case KEY_DOWN:
			snakeDirection = Direction::DOWN;
			break;
		case KEY_LEFT:
			snakeDirection = Direction::LEFT;
			break;
		case KEY_RIGHT:
			snakeDirection = Direction::RIGHT;
			break;
		}
	}
}

void justifyPosition(Position &player) {
	if (player.x <= 0)
		player.x = 1;
	else if (player.x >= WIDTH - 1)
		player.x = WIDTH - 2;

	if (player.y <= 0)
		player.y = 1;
	else if (player.y >= HEIGHT - 1)
		player.y = HEIGHT - 2;
}

void Logic() {
	if (Snake::isDead())
		gameOver = true;
	switch (snakeDirection)
	{
	case Direction::UP:
		snakePos.y--;
		break;
	case Direction::DOWN:
		snakePos.y++;
		break;
	case Direction::LEFT:
		snakePos.x--;
		break;
	case Direction::RIGHT:
		snakePos.x++;
		break;
	}
	justifyPosition(snakePos);
	Snake::move(snakePos.x, snakePos.y);

	if (snakePos.x == fruitPos.x && snakePos.y == fruitPos.y) {
		do {
			fruitPos.x = std::rand() % (WIDTH - 2) + 1;
			fruitPos.y = std::rand() % (HEIGHT - 2) + 1;
		} while (snakePos.x == fruitPos.x && snakePos.y == fruitPos.y);
		Snake::grow();
	}

}

void CleanUp() {
	ScreenBuffer::deposeBuffer();
}