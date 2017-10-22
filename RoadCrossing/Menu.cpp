#include "Menu.h"

short Menu::findMiddleH()
{
	return CONSOLE_H / 2 - menuFig->Height() / 2 - menuFig->Height() % 2;
}

short Menu::findMiddleW(string menuTitle)
{
	return CONSOLE_W / 2 - menuTitle.length() / 2 - menuTitle.length() % 2;
}

Menu::Menu()
{
}

Menu::Menu(short consoleW, short consoleH)
{
	CONSOLE_H = consoleH;
	CONSOLE_W = consoleW;
	menuFig = new Figure("Figure\\Menu.txt");
	pastRow = 3;
	currentRow = 4;		//Tiêu đề bắt đầu ở dòng thứ 2 từ trên xuống
						//dòng đầu tiên là dòng 0
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
	if (currentRow == menuFig->Height() - 1 - 4)
		return;
	pastRow = currentRow;
	currentRow++;
}

void Menu::Enter() // truyền biến tiểu trình?
{
	this->Down();
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

void Menu::Print()
{
	int x, y;
	vector<string> str = menuFig->Get();
	for (int rowIndex = 0; rowIndex < menuFig->Height(); rowIndex++)
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
		else if (rowIndex == 1 || rowIndex == menuFig->Height() - 1 - 1)
		{
			TextColor(15);
			printf(" %s ", str[rowIndex].c_str());
		}
		else if (rowIndex == 0 || rowIndex == menuFig->Height() - 1)
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
