#pragma once

namespace ScreenBuffer {
	void SetupBufferScreen(const int &width, const int &height);
	void drawToBuffer(int x, int y, char c);
	void drawToConsole();
	void deposeBuffer();
}