#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <Windows.h>
#include <cstdio>

#define CONSOLE_MAX_HEIGHT 70
#define CONSOLE_MAX_WIDTH 200

#define smallFontSizeW (short)GetSystemMetrics(SM_CXSCREEN)/CONSOLE_MAX_WIDTH - 3	// = 6
#define smallFontSizeH (short)GetSystemMetrics(SM_CYSCREEN)/CONSOLE_MAX_HEIGHT 	- 3	// = 12

#define CONSOLE_MENU_HEIGHT 28		//28 23
#define CONSOLE_MENU_WIDTH	100		//100 70

#define bigFontSizeW (short)GetSystemMetrics(SM_CXSCREEN)/CONSOLE_MENU_WIDTH  - 2 		// = 17
#define bigFontSizeH (short)GetSystemMetrics(SM_CYSCREEN)/CONSOLE_MENU_HEIGHT  - 2		// = 36
// important: smallFontSizeW * CONSOLE_MAX_WIDTH == bigFontSizeW * CONSOLE_MENU_WIDTH
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

void FixConsoleWindow(int width = CONSOLE_MAX_WIDTH, int height = CONSOLE_MAX_HEIGHT);
BOOL SetConsoleFontSize(COORD dwFontSize, const wchar_t *fontName);
void DrawBoard();
void GotoXY(int, int);
void GotoXY(COORD);
COORD GetCursorPosition();
void TextColor(short);

#endif // !_CONSOLE_H
