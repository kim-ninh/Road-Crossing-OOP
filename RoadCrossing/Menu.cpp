#include "Menu.h"

short Menu::findMiddleH()
{
	return CONSOLE_H / 2 - menuFig.Height() / 2 - menuFig.Height() % 2;
}

short Menu::findMiddleW(string menuTitle)
{
	return CONSOLE_W / 2 - menuTitle.length() / 2 - menuTitle.length() % 2;
}

short Menu::findLongestStrPos(vector<string> text)
{
	short pos, longestStr = text[0].length();
	for (int i = 0; i < text.size(); i++)
	{
		if (longestStr < text[i].length())
		{
			longestStr = text[i].length();
			pos = i;
		}
	}
	return pos;
}

Menu::Menu()
{
	CONSOLE_H = CONSOLE_MENU_HEIGHT; 
	CONSOLE_W = CONSOLE_MENU_WIDTH;
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
		printf(" %s ", s.c_str());
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

	aboutSection.Set("Figure\\About.txt");
	helpSection.Set("Figure\\Instruction.txt");
		
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
// ===============  Testing Area =====================
void Menu::PrintHelp()
{
	GotoXY(0, 0);
	vector<string> str = helpSection.Get();
	TextColor(15);
	for (int rowIndex = 0; rowIndex < helpSection.Height(); rowIndex++)
		printf("%s\n", str[rowIndex].c_str());
}

void Menu::PrintAbout(short y)
{
	vector<string> str = aboutSection.Get();
	short x;

	for (int rowIndex = 0; rowIndex < aboutSection.Height(); rowIndex++)
	{
		if (y + rowIndex < CONSOLE_H && y + rowIndex >= 0)
		{
			x = findMiddleW(str[rowIndex]);
			GotoXY(x, y + rowIndex);
			printf("%s", str[rowIndex].c_str());
		}
	}

}

void Menu::AboutAnimation()
{
	short y;
	y = CONSOLE_H;
	TextColor(15);
	while (true)
	{
		if (y + aboutSection.Height() == 0)
			y = CONSOLE_H;
		EraseAboutSection();
		PrintAbout(y);

		y--;
		Sleep(400);
		
	}
}

void Menu::EraseMenu()
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
		printf(" %s ", s.c_str());
	}
}

void Menu::EraseHelpSection()
{
	GotoXY(0, 0);
	vector<string> str = helpSection.Get();
	TextColor(15);
	for (int rowIndex = 0; rowIndex < helpSection.Height(); rowIndex++)
	{
		string s;
		short len = str[rowIndex].length();
		for (int i = 0; i < len; i++)
			s += ' ';
		printf("%s\n", s.c_str());
	}
}

void Menu::EraseAboutSection()
{
	short x;
	vector<string> str = aboutSection.Get();
	int pos = findLongestStrPos(str);
	x = findMiddleW(str[pos]);
	string s;
	for (int i = 0; i < str[pos].length(); i++)
		s += ' ';
	
	for (int i = 0; i < CONSOLE_H; i++)
	{
		GotoXY(x, i);
		printf("%s", s.c_str());
	}
}

