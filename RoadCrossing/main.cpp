
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include "Game.h"
#include "Console.h"
#include "Frame.h"
#include "Car.h"
#include "Truck.h"
#include "Bird.h"
#include "Dinosaur.h"
#include <conio.h>
#include <mutex>

using namespace std;

void SubThread() {
	Obstacle *ob = new Car(BOARD_LEFT_EDGE, 50, RIGHT);
	COORD pos;
	while (true) {
		pos = GetCursorPosition();
		lock_guard<mutex> lock(theLock);

		ob->Move();
		ob->Print();
		GotoXY(pos);
		Sleep(25);
	}

	delete ob;
}

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

	SetConsoleFontSize({ 7, 12 });

	FixConsoleWindow();
	DrawBoard();


	thread t1(SubThread);
	
	char temp;
	People people(50, 20);
	COORD pos = GetCursorPosition();
	{
		lock_guard<mutex> lock(theLock);
		people.Print();
	}
	GotoXY(pos);

	while (true) {
		temp = _getch();
		char ch = toupper(temp);

		if (ch == 'A') {
			people.Left(0);
		}
		else if (ch == 'D') {
			people.Right(0);
		}
		else if (ch == 'S') {
			people.Down(0);
		}
		else if (ch == 'W') {
			people.Up(0);
		}
		
		lock_guard<mutex> lock(theLock);
		people.Print();
	}




	cin.get();
	return 0;
}

