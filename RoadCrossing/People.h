#pragma once
#ifndef _PEOPLE_H
#define _PEOPLE_H

#include "Obstacle.h"

class People
{
public:
	int mX, mY;
	bool mStage;		// true: sống, false: chết
	static Figure fig;
	vector<COORD> oldPos;
public:
	People(int x = 0, int y = 0);
	void Up();
	void Left();
	void Right();
	void Down();
	void Move(char);
	bool IsImpact(const Obstacle*&);
	bool IsFinish();
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
