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
void Figure::Set(const char * file_name)
{
	if (!str.empty()) {
		str.clear();
	}

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

void Figure::Print(COORD coord, bool edge)
{
	Print(coord.X, coord.Y, edge);
}

void Figure::Print(int x, int y, bool edge)
{
	if (edge) {
		if (x > BOARD_GAME_LEFT) {
			if (x + width - 1 < BOARD_GAME_RIGHT) {			// vật còn nguyên
				for (int i = 0; i < height; i++) {
					GotoXY(x, y + i);
					printf("%s", str[i].c_str());
				}
			}
			else {				// đang đi vào/ra cạnh phải (bị khuất 1 phần)

				for (int i = 0; i < height; i++) {

					// in nửa phần bên cạnh phải
					for (int j = 0; j < BOARD_GAME_RIGHT - x; j++) {
						GotoXY(x + j, i + y);
						//lock_guard<mutex> lock(theLock);
						printf("%c", str[i].c_str()[j]);
					}
				}
			}
		}
		else {
			int d = BOARD_GAME_LEFT - x + 1;			// khoảng bị khuất bên cạnh trái

			for (int i = 0; i < height; i++) {
				GotoXY(BOARD_GAME_LEFT + 1, y + i);
				printf("%s", str[i].c_str() + d);
			}
		}
	}
	else {
		for (int i = 0; i < height; i++) {
			GotoXY(x, y + i);
			printf("%s", str[i].c_str());
		}
	}
}

void Figure::PrintIntro(COORD pos)
{
	for (int i = 0; i < height; i++) {
		GotoXY(pos.X, pos.Y + i);
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

void Figure::Write(ostream & outDev)
{
	outDev.write((char*)&width, sizeof(width));
	outDev.write((char*)&height, sizeof(height));

	for (int i = 0; i < height; i++) {
		int length = str[i].length();
		outDev.write((char*)&length, sizeof(length));
		outDev.write(str[i].c_str(), sizeof(char)*length);
	}
}

void Figure::Read(istream & inDev)
{
	inDev.read((char*)&width, sizeof(width));
	inDev.read((char*)&height, sizeof(height));

	str.resize(height);
	int length;

	for (int i = 0; i < height; i++) {
		inDev.read((char*)&length, sizeof(length));
		str[i].resize(length);
		inDev.read((char*)&str[i][0], sizeof(char)*length);
	}
}

Figure Figure::operator+(Figure & fig)
{
	if (height != fig.height) {
		return *this;
	}

	Figure figure;
	
	for (int i = 0; i < height; i++) {
		figure.str.push_back(str[i] + fig.str[i]);
	}

	figure.width = width + fig.width;
	figure.height = height;

	return figure;
}
