#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <Windows.h>
#include <cstdio>

#define CONSOLE_MAX_HEIGHT 70		//70  80
#define CONSOLE_MAX_WIDTH 200		//200 228

#define smallFontSizeW (short)GetSystemMetrics(SM_CXSCREEN)/CONSOLE_MAX_WIDTH - 3	// = 6 //- 3
#define smallFontSizeH (short)GetSystemMetrics(SM_CYSCREEN)/CONSOLE_MAX_HEIGHT 	- 3	// = 12 //-3

#define CONSOLE_MENU_HEIGHT 23		//28 23 23
#define CONSOLE_MENU_WIDTH	70		//100 70 66

#define bigFontSizeW (short)GetSystemMetrics(SM_CXSCREEN)/CONSOLE_MENU_WIDTH  -  10		// = 17  //-10
#define bigFontSizeH (short)GetSystemMetrics(SM_CYSCREEN)/CONSOLE_MENU_HEIGHT  - 10		// = 36	 //-10
// important: smallFontSizeW * CONSOLE_MAX_WIDTH == bigFontSizeW * CONSOLE_MENU_WIDTH			// ~1200
//			&&smallFontSizeH * CONSOLE_MAX_HEIGHT == bigFontSizeH * CONSOLE_MENU_HEIGHT

#define WIDTH_OFFSET 20
#define HEIGHT_OFFSET 4

#define BOARD_LEFT_EDGE WIDTH_OFFSET		// Cạnh trái của khung Game (x)
#define BOARD_RIGHT_EDGE (CONSOLE_MAX_WIDTH - WIDTH_OFFSET - 1)		// Cạnh phải (x)
#define BOARD_TOP_EDGE  HEIGHT_OFFSET			// Cạnh trên (y)
#define BOARD_BOTTOM_EDGE (CONSOLE_MAX_HEIGHT - HEIGHT_OFFSET - 1)		// Cạnh dưới (y)

#define BOARD_GAME_TOP BOARD_TOP_EDGE
#define BOARD_GAME_BOTTOM (BOARD_BOTTOM_EDGE - 0)
#define BOARD_GAME_LEFT BOARD_LEFT_EDGE
#define BOARD_GAME_RIGHT (BOARD_RIGHT_EDGE - 0)

#pragma region Color
// DOS colors; you can use these values if you don't wish to bitwise OR the
// blue-red-green-intensity bits yourself
#define FOREGROUND_BLACK        0x0000  // text color is black
#define FOREGROUND_BLUE         0x0001  // text color is blue
#define FOREGROUND_GREEN        0x0002  // text color is green
#define FOREGROUND_CYAN         0x0003  // text color is cyan
#define FOREGROUND_RED          0x0004  // text color is red
#define FOREGROUND_MAGENTA      0x0005  // text color is magenta
#define FOREGROUND_BROWN        0x0006  // text color is brown
#define FOREGROUND_LIGHTGRAY    0x0007  // text color is lightgray
#define FOREGROUND_DARKGRAY     0x0008  // text color is darkgray
#define FOREGROUND_LIGHTBLUE    0x0009  // text color is lightblue
#define FOREGROUND_LIGHTGREEN   0x000A  // text color is lightgreen
#define FOREGROUND_LIGHTCYAN    0x000B  // text color is lightcyan
#define FOREGROUND_LIGHTRED     0x000C  // text color is lightred
#define FOREGROUND_LIGHTMAGENTA 0x000D  // text color is lightmagenta
#define FOREGROUND_YELLOW       0x000E  // text color is yellow
#define FOREGROUND_WHITE        0x000F  // text color is white
#define BACKGROUND_BLACK        0x0000  // background color is black
#define BACKGROUND_BLUE         0x0010  // background color is blue
#define BACKGROUND_GREEN        0x0020  // background color is green
#define BACKGROUND_CYAN         0x0030  // background color is cyan
#define BACKGROUND_RED          0x0040  // background color is red
#define BACKGROUND_MAGENTA      0x0050  // background color is magenta
#define BACKGROUND_BROWN        0x0060  // background color is brown
#define BACKGROUND_LIGHTGRAY    0x0070  // background color is lightgray
#define BACKGROUND_DARKGRAY     0x0080  // background color is darkgray
#define BACKGROUND_LIGHTBLUE    0x0090  // background color is lightblue
#define BACKGROUND_LIGHTGREEN   0x00A0  // background color is lightgreen
#define BACKGROUND_LIGHTCYAN    0x00B0  // background color is lightcyan
#define BACKGROUND_LIGHTRED     0x00C0  // background color is lightred
#define BACKGROUND_LIGHTMAGENTA 0x00D0  // background color is lightmagenta
#define BACKGROUND_YELLOW       0x00E0  // background color is yellow
#define BACKGROUND_WHITE        0x00F0  // background color is white

#pragma endregion

void FixConsoleWindow(int width = CONSOLE_MAX_WIDTH, int height = CONSOLE_MAX_HEIGHT);
BOOL SetConsoleFontSize(COORD dwFontSize, const wchar_t *fontName);
void DrawBoard();
void GotoXY(int, int);
void GotoXY(COORD);
COORD GetCursorPosition();
void TextColor(short);

#endif // !_CONSOLE_H
