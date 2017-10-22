#pragma once
#include"Figure.h"
class Menu
{
private:
	short CONSOLE_W;
	short CONSOLE_H;
	Figure *menuFig;
	short pastRow;
	short currentRow;
	short findMiddleH();
	short findMiddleW(string menuTitle);
public:
	Menu();
	Menu(short consoleW, short consoleH);
	
	void Up();
	void Down();
	void Enter(); //truyền biến tiểu trình?
	void Control(char KEY);

	void Print();	//Tự canh lề rồi in
};