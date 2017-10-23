#pragma once
#include "Figure.h"

#define MAX 1024
Figure::Figure() {}
Figure::Figure(const char * file_name)
{
	ifstream inFile(file_name);
	width = height = 0;
	char buf[MAX + 1];

	while (!inFile.eof()) {
		inFile.getline(buf, MAX);
		str.push_back(string(buf));
		height++;
	}
	width = str[0].length();
}
string Figure::Get(char * file_name)
{
	std::wifstream wif(file_name);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();

	wstring wstr = wss.str();
	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	char* m = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, m, bufferSize, NULL, NULL);

	string temp(m);
	delete[] m;
	return temp;
}

vector<string>& Figure::Get()
{
	return str;
}

void Figure::Print(COORD coord)
{
	Print(coord.X, coord.Y);
}

void Figure::Print(int x, int y)
{
	if (x > BOARD_GAME_LEFT) {			
		if (x + width - 1 < BOARD_GAME_RIGHT) {			// vật còn nguyên
			for (int i = 0; i < height; i++) {
				GotoXY(x, y + i);
				//lock_guard<mutex> lock(theLock);
				printf("%s", str[i].c_str());
				//cout << str[i];
			}
		}
		else {				// đang đi vào/ra cạnh phải (bị khuất 1 phần)

			//int d = BOARD_GAME_RIGHT - x + 1;

			for (int i = 0; i < height; i++) {

				// in nửa phần bên cạnh phải
				for (int j = 0; j < BOARD_GAME_RIGHT - x; j++) {
					GotoXY(x + j, i + y);
					//lock_guard<mutex> lock(theLock);
					printf("%c", str[i].c_str()[j]);
				}

				// in nửa phần bên cạnh trái
				
				//GotoXY(BOARD_GAME_LEFT + 1,i + y);
				//printf("%s", str[i].c_str() + d);
			}
		}
	}
	else {
		int d = BOARD_GAME_LEFT - x + 1;			// khoảng bị khuất bên cạnh trái

		for (int i = 0; i < height; i++) {
			GotoXY(BOARD_GAME_LEFT + 1, y + i);
			//lock_guard<mutex> lock(theLock);
			printf("%s", str[i].c_str() + d);
		}
	}
}

void Figure::PrintIntro(COORD pos)
{
	for (int i = 0; i < height; i++) {
		GotoXY(pos.X, pos.Y + i);
		//lock_guard<mutex> lock(theLock);
		printf("%s", str[i].c_str());
		Sleep(100);
	}
}

int Figure::Width()
{
	return width;
}

int Figure::Height()
{
	return height;
}