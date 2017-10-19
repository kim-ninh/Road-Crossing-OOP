﻿#pragma once
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <Windows.h>
#include <cstdio>

#define CONSOLE_MAX_HEIGHT 80
#define CONSOLE_MAX_WIDTH 200

#define WIDTH_OFFSET 20
#define HEIGHT_OFFSET 3

#define BOARD_LEFT_EDGE WIDTH_OFFSET		// Cạnh trái của khung Game (x)
#define BOARD_RIGHT_EDGE (CONSOLE_MAX_WIDTH - WIDTH_OFFSET - 1)		// Cạnh phải (x)
#define BOARD_TOP_EDGE  HEIGHT_OFFSET			// Cạnh trên (y)
#define BOARD_BOTTOM_EDGE (CONSOLE_MAX_HEIGHT - HEIGHT_OFFSET - 1)		// Cạnh dưới (y)

#define BOARD_GAME_TOP BOARD_TOP_EDGE
#define BOARD_GAME_BOTTOM (BOARD_TOP_EDGE - 10)
#define BOARD_GAME_LEFT BOARD_LEFT_EDGE
#define BOARD_GAME_RIGHT (BOARD_RIGHT_EDGE - 10)

void FixConsoleWindow();
BOOL SetConsoleFontSize(COORD dwFontSize);
void DrawBoard();
void GotoXY(int, int);
void GotoXY(COORD);
COORD GetCursorPosition();


#endif // !_CONSOLE_H
