#pragma once
#ifndef _MENU_H
#define _MENU_H

#include"Figure.h"
#include <conio.h>


class Menu
{
private:
	short CONSOLE_W;
	short CONSOLE_H;
	Figure menuFig;
	Figure aboutSection;
	Figure helpSection;
	short pastRow;
	short currentRow;
	short findMiddleH();
	short findMiddleW(string menuTitle);
	short findLongestStrPos(vector<string>);
public:
	Menu();
	Menu(short consoleW, short consoleH);
	void Erase();

	/**
	 * \brief 
	 * \param menuType: main, pause, lose
	 */
	void Set(const char *menuType);	// set kiểu cho menu

	void Up();
	void Down();
	void Enter(); //truyền biến tiểu trình?
	void Control(char KEY);
	string Select();
	void Print();	//Tự canh lề rồi in

	//=======================Testing Function 
	void PrintHelp();
	void PrintAbout(short);
	void AboutAnimation();
	void EraseMenu();
	void EraseHelpSection();
	void EraseAboutSection();
	void Write(ostream&);
	void Read(istream&);
};

#endif // !_MENU_H
