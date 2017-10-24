
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include "Console.h"
#include "Frame.h"
#include "Car.h"
#include "Truck.h"
#include "Bird.h"
#include "Dinosaur.h"
#include "Game.h"
#include "Menu.h"
#include <conio.h>
#include <mutex>

using namespace std;

//void SubThread() {
//	Obstacle *ob = new Truck(BOARD_LEFT_EDGE, 50, RIGHT);
//	COORD pos;
//	while (true) {
//		pos = GetCursorPosition();
//		lock_guard<mutex> lock(theLock);
//
//		ob->Move();
//		ob->Print();
//		GotoXY(pos);
//		Sleep(25);
//	}
//
//	delete ob;
//}

Game game;

int main() {

#pragma region MyRegion
	////truck.resize(3);
	////truck[0] = " ▄   ██▄▄ ";
	////truck[1] = " █████████";
	////truck[2] = "   ○   ○  ";
	////

	////FixConsoleWindow();
	////UINT oldcp = GetConsoleOutputCP();
	////SetConsoleOutputCP(CP_UTF8);



	//////wstring wstr = readFile("Figure\\Truck.txt");
	//////int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	//////char* m = new char[bufferSize];
	//////WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, m, bufferSize, NULL, NULL);
	//////wprintf(L"%S", m);

	//////delete[] m;

	//////GotoXY(20, 20);
	//////string car = Figure::Get("Figure\\Car.txt");
	//////wprintf(L"%S", car.c_str());
	//////string truck = Figure::Get("Figure\\Truck.txt");
	//////wprintf(L"\n%S", truck.c_str());

	////Figure car("Figure\\Car3.txt");
	////
	////cout << car << endl;
	////car.Reverse();
	////cout << car;
	////Truck t;
	////

	////SetConsoleOutputCP(oldcp);
#pragma endregion

	//ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	//SetConsoleFontSize({ 10, 18 });	

	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//GetConsoleScreenBufferInfo(ConsoleHanlde, &csbi);
	//cout << csbi.srWindow.Bottom;


	FixConsoleWindow();
	DrawBoard();

	
	//PlaySound("Sound\\TheFatRat_Unity.wav", NULL, SND_LOOP);

	Game game;
	game.StartGame();


	_getch();
	return 0;
}

