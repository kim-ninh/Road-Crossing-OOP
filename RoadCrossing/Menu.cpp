#include "Menu.h"

short Menu::findMiddleH()
{
	return CONSOLE_H / 2 - menuFig.Height() / 2 - menuFig.Height() % 2;
}

short Menu::findMiddleW(string menuTitle)
{
	return CONSOLE_W / 2 - menuTitle.length() / 2 - menuTitle.length() % 2;
}

Menu::Menu()
{
	CONSOLE_H = CONSOLE_MAX_HEIGHT;
	CONSOLE_W = CONSOLE_MAX_WIDTH;
	//menuFig = Figure("Figure\\Menu.txt");
	this->Set("main");
	pastRow = 3;
	currentRow = 4;		//Tiêu đề bắt đầu ở dòng thứ 2 từ trên xuống
						//dòng đầu tiên là dòng 0
}

Menu::Menu(short consoleW, short consoleH)
{
	CONSOLE_H = consoleH;
	CONSOLE_W = consoleW;
	//menuFig = Figure("Figure\\Menu.txt");
	this->Set("main");
	pastRow = 3;
	currentRow = 4;		//Tiêu đề bắt đầu ở dòng thứ 2 từ trên xuống
						//dòng đầu tiên là dòng 0
}

void Menu::Erase()
{
	short x, y;
	vector<string> str = menuFig.Get();
	string s;
	for (int rowIndex = 0; rowIndex < menuFig.Height(); rowIndex++)
	{
		int len = str[rowIndex].length();
		
		for (int i = 0; i < len; i++) {
			s += ' ';
		}
		
		x = findMiddleW(str[rowIndex]) - 1;
		y = findMiddleH() + rowIndex;
		GotoXY(x, y);
		printf("%s", s.c_str());
	}
}

void Menu::Set(const char * menuType)
{
	if (strcmp(menuType, "main") == 0)
		menuFig.Set("Figure\\Main_Menu.txt");
	else if (strcmp(menuType, "pause") == 0)
		menuFig.Set("Figure\\Pause_Menu.txt");
	else if (strcmp(menuType, "lose") == 0)
		menuFig.Set("Figure\\Lose_Menu.txt");
		
}

void Menu::Up()
{
	if (currentRow == 4)
		return;
	pastRow = currentRow;
	currentRow--;
}

void Menu::Down()
{
	if (currentRow == menuFig.Height() - 1 - 4)
		return;
	pastRow = currentRow;
	currentRow++;
}

void Menu::Enter() // truyền biến tiểu trình?
{	
	
}

void Menu::Control(char KEY)
{
	switch (KEY)
	{
	case'W': this->Up(); break;
	case'S': this->Down(); break;
	case 13: this->Enter(); break;		//Mã ASCII của Enter: 13
	}
}

string Menu::Select()
{
	Print();
	while (true)
	{
		char ch = toupper(_getch());
		switch (ch)
		{
		case'W': this->Up(); PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC); break;
		case'S': this->Down(); PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC); break;
		case 13: 
			TextColor(15);
			PlaySound("Sound\\sfx_menu_select4.wav", NULL, SND_ASYNC);
			return menuFig.Get()[currentRow];		//Mã ASCII của Enter: 13
		}

		Print();
		Sleep(50);
	}
}

void Menu::Print()
{
	short x, y;
	vector<string> str = menuFig.Get();
	for (int rowIndex = 0; rowIndex < menuFig.Height(); rowIndex++)
	{
		x = findMiddleW(str[rowIndex]) - 1;
		y = findMiddleH() + rowIndex;
		GotoXY(x, y);
		if (currentRow == rowIndex)
		{
			TextColor(14);
			printf(">%s<", str[rowIndex].c_str());
		}
		else if (pastRow == rowIndex && pastRow != 1)
		{
			TextColor(6);
			printf(" %s ", str[rowIndex].c_str());
		}
		else if (rowIndex == 1 || rowIndex == menuFig.Height() - 1 - 1)
		{
			TextColor(15);
			printf(" %s ", str[rowIndex].c_str());
		}
		else if (rowIndex == 0 || rowIndex == menuFig.Height() - 1)
		{
			TextColor(11);
			printf(" %s ", str[rowIndex].c_str());
		}
		else
		{
			TextColor(6);
			printf(" %s ", str[rowIndex].c_str());
		}
	}
}
