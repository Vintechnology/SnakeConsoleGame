# SnakeConsoleGame
A simple snake game on console

# How to use ScreenBufer
**ScreenBuffer** is a namespace which contains all function you need to draw characters to the console screen in a Console Game (or command line game). It implements buffer drawing method which makes your game graphics more stable.

First, include the header file.
```C++
#include "ScreenBuffer.h"
```

Before using, **make sure** that you've called. 
```C++
ScreenBuffer::SetupBufferScreen(const int &width, const int &height);
```
`width` and `height` are the area on the screen you wish to draw on.
You just need to do this once in a program.

ScreenBuffer treats console window as a `width x height` matrix which indeces are from 0 to width-1 (or height-1 on the y axis).
_Note_: the (0,0) position is your **top left** corner on the screen. As y increases, we will go down in the console windows. As x increases, we will move to the right of the console windows.

## Draw to buffer
We don't try to draw to the console as fast as possible. Instead, we draw all our screen to a *buffer* and draw that buffer to the screen as we finish drawing.

```C++
ScreenBuffer::drawToBuffer(int x, int y, char c);
```
fills position 'x', 'y' in the buffer with character 'c'. By this time, don't pass the '\n' character for the sake of your program.

## Draw to screen
```C++
ScreenBuffer::drawToConsole();
```
will put your things on the screen. Make sure to call this function as you finish updating your screen.

## Clean up after use
```C++
ScreenBuffer::deposeBuffer();
```
This function frees up the buffer. Make sure to call it after you've done using the buffer to prevent memory leaks.

For an example, check other files. Start with main.cpp for an example snake game.
