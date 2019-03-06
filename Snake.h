#pragma once

namespace Snake {
	void initSnake(int x, int y);
	void grow();
	void move(int x, int y);
	void drawSnake();
	bool isDead();
	void die();

}