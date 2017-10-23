#pragma once
#ifndef _FIGURE_H
#define _FIGURE_H

#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <codecvt>
#include "Console.h"
#include <iostream>
#include <mutex>

using namespace std;

static mutex theLock;

class Figure
{
	friend class People;
private:
	vector<string> str;
	int width, height;
public:
	Figure();
	Figure(const char *file_name);
	string Get(char *file_name);
	vector<string>& Get();
	void Print(COORD);
	void Print(int, int);
	void PrintIntro(COORD);
	int Width();
	int Height();
};


#endif // !_FIGURE_H
