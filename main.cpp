#include <iostream>
#include <windows.h>
#include "Game.h"

void setCursorVisible(bool isVisible) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(out, &cursorInfo);
}


int main()
{
	setCursorVisible(false);

	SetUp();
	Draw();
	while (!gameOver) {
		Sleep(100);
		Update();
	}

	CleanUp();
}
