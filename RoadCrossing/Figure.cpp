#pragma once
#include "Figure.h"

#define MAX 1024
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

void Figure::Print(COORD coord)
{
	for (int i = 0; i < width; i++) {
		GotoXY(coord.X, coord.Y + i);
		cout << str[i];
	}
}

void Figure::Print(int x, int y)
{
	if (x > BOARD_LEFT_EDGE) {
		if (x + width - 1 < BOARD_RIGHT_EDGE) {
			for (int i = 0; i < height; i++) {
				GotoXY(x, y + i);
				lock_guard<mutex> lock(theLock);
				printf("%s", str[i].c_str());
				//cout << str[i];
			}
		}
		else {
			for (int i = 0; i < height; i++) {
				
				for (int j = 0; j < BOARD_RIGHT_EDGE - x; j++) {
					GotoXY(x + j, i + y);
					printf("%c", str[i].c_str()[j]);
				}
			}
		}
	}
	else {
		int d = BOARD_LEFT_EDGE - x + 1;

		for (int i = 0; i < height; i++) {
			GotoXY(BOARD_LEFT_EDGE + 1, y + i);
			printf("%s", str[i].c_str() + d);
		}
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