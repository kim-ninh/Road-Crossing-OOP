#pragma once
#include "Console.h"

void FixConsoleWindow(int width, int height)
{
	// Cố định cửa sổ console, ngăn người dùng thay đổi kích thước và làm mờ nút Maximize
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	// Ẩn con trỏ của màn hình Console
	CONSOLE_CURSOR_INFO info;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(ConsoleHandle, &info);

	// Cố định kích thước buffer của cửa sổ Console với một Size xác định
	/*COORD ConsoleBufferSize = { CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT };*/
	COORD ConsoleBufferSize = { width, height };
	SetConsoleScreenBufferSize(ConsoleHandle, ConsoleBufferSize);

	// Cố dịnh kích thước cửa sổ Console với một Size xác định
	SMALL_RECT Rect = { 0,0,ConsoleBufferSize.X - 1,ConsoleBufferSize.Y - 1 };
	SetConsoleWindowInfo(ConsoleHandle, TRUE, &Rect);
}

BOOL SetConsoleFontSize(COORD dwFontSize, const wchar_t *fontName) {
	//HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };

	//if (!GetCurrentConsoleFontEx(output, false, &info))
	//	return false;

	//info.dwFontSize = dwFontSize;
	//info.FontFamily = FF_DONTCARE;
	//info.FontWeight = FW_NORMAL;
	////wcscpy(info.FaceName, L"Lucida Console");
	//wcscpy(info.FaceName, L"Lucida Console");
	//return SetCurrentConsoleFontEx(output, false, &info);
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return false;
	info.dwFontSize = dwFontSize;
	wcscpy_s(info.FaceName, fontName);
	return SetCurrentConsoleFontEx(output, false, &info);
}

void DrawBoard(void)
{
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
	GotoXY({ BOARD_LEFT_EDGE, BOARD_TOP_EDGE });		// Góc trên bên trái
	printf("%c", 201);
	GotoXY({ BOARD_RIGHT_EDGE, BOARD_TOP_EDGE });		// Góc trên bên phải
	printf("%c", 187);
	GotoXY({ BOARD_LEFT_EDGE, BOARD_BOTTOM_EDGE });		// Góc dưới bên trái
	printf("%c", 200);
	GotoXY({ BOARD_RIGHT_EDGE, BOARD_BOTTOM_EDGE });	//Góc dưới bên phải
	printf("%c", 188);

	GotoXY(BOARD_LEFT_EDGE + 1, BOARD_TOP_EDGE);
	for (short i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++)	// Cạnh trên
	{
		//GotoXY({ i, BOARD_TOP_EDGE });
		printf("%c", 205);
	}

	GotoXY(BOARD_LEFT_EDGE + 1, BOARD_BOTTOM_EDGE);
	for (short i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++)	// Cạnh dưới
	{
		//GotoXY({ i, BOARD_BOTTOM_EDGE });
		printf("%c", 205);
	}

	for (short i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++)	// Cạnh trái
	{
		GotoXY({ BOARD_LEFT_EDGE, i });
		printf("%c", 186);
	}

	for (short i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++)	// Cạnh phải
	{
		GotoXY({ BOARD_RIGHT_EDGE, i });
		printf("%c", 186);
	}
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE ConsoleHanle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHanle, coord);
}

void GotoXY(COORD coord)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ConsoleHandle, coord);
}

COORD GetCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD pos;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &csbi)) {
		pos = { 0,0 };
	}
	
	pos = csbi.dwCursorPosition;
	return pos;
}

void TextColor(short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearConsole()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
	
	std::string s(csbi.srWindow.Right + 1, ' ');
	for (int i = 0; i <= csbi.srWindow.Bottom; i++) {
		GotoXY(0, i);
		printf("%s", s.c_str());
	}
}

SMALL_RECT GetWindowSize()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO info;

	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);		// lấy thông tin kích thước cửa sở và buffer của console
															// ở đây chỉ quan tâm kích thước cửa sổ
	return csbi.srWindow;
}
