#include <iostream>
#include <windows.h>
#include "ScreenBuffer.h"

namespace ScreenBuffer {
	char *currentFrame = nullptr;
	char *nextFrame = nullptr;
	const int *WIDTH;
	const int *HEIGHT;

	void gotoXY(int x, int y) {
		static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // TODO: should I set it global???
		COORD coord = { x,y };
		SetConsoleCursorPosition(out, coord);
	}

	void cls()
	{
		// Get the Win32 handle representing standard output.
		// This generally only has to be done once, so we make it static.
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD topLeft = { 0, 0 };

		// std::cout uses a buffer to batch writes to the underlying console.
		// We need to flush that to the console because we're circumventing
		// std::cout entirely; after we clear the console, we don't want
		// stale buffered text to randomly be written out.
		std::cout.flush();

		// Figure out the current width and height of the console window
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
			// TODO: Handle failure!
			abort();
		}
		DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

		DWORD written;

		// Flood-fill the console with spaces to clear it
		FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

		// Reset the attributes of every character to the default.
		// This clears all background colour formatting, if any.
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

		// Move the cursor back to the top left for the next sequence of writes
		SetConsoleCursorPosition(hOut, topLeft);
	}

	char* initBuffer() {
		int width = *WIDTH;
		int height = *HEIGHT;

		char* buffer = new char[width*height + height+1];

		for (int i = 0; i < height; i++) {
			buffer[i*width + width + i] = '\n';
		}

		buffer[width*height + height] = '\0';
		return buffer;
	}

	void SetupBufferScreen(const int &width, const int &height) {
		if (nextFrame != nullptr)
			return;

		WIDTH = &width;
		HEIGHT = &height;

		nextFrame = initBuffer();
	}



	int getBufferIndex(int x, int y) {
		if (x < 0 || y < 0 || x >= *WIDTH || y >= *HEIGHT)
			return -1;
		return y * (*WIDTH) + x + y;
	}

	void drawToBuffer(int x, int y, char c) {
		int bufferIndex = getBufferIndex(x, y);
		nextFrame[bufferIndex] = c;
	}

	void drawToConsole() {
		if (currentFrame == nullptr) {
			std::cout << nextFrame;
			currentFrame = initBuffer();
		}
		else {

			for (int y = 0; y < (*HEIGHT); y++) {
				for (int x = 0; x < (*WIDTH); x++) {

					int index = getBufferIndex(x, y);
					if (currentFrame[index] != nextFrame[index]) {
						gotoXY(x, y);
						std::cout << nextFrame[index];
					}

				}
			}

		}
		
		std::cout.flush();
		char* temp = currentFrame;
		currentFrame = nextFrame;
		nextFrame = temp;
	}

	void deposeBuffer() {
		delete[] currentFrame;
		delete[] nextFrame;
		currentFrame = nullptr;
		nextFrame = nullptr;
	}
}
