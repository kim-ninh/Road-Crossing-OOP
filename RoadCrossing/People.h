#pragma once
#ifndef _PEOPLE_H
#define _PEOPLE_H

#include "Figure.h"
#include "Console.h"

class People
{
private:
	int mX, mY;
	bool mStage;		// true: sống, false: chết
	static Figure fig;
	vector<COORD> oldPos;

	void Up();
	void Left();
	void Right();
	void Down();
public:
	People(int x = 0, int y = 0);
	void Move(char);
	bool IsDead();
	void Print();
	void EraseOld();
	COORD GetPosition();
	Figure& GetFigure();
	int Width();
	int Height();
	void SetStage(bool);
	void Write(ostream& outDev);
	void Read(istream& inDev);
};
#endif // !_PEOPLE_H
