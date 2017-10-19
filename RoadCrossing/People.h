#pragma once
#ifndef _PEOPLE_H
#define _PEOPLE_H

#include "Obstacle.h"

class People
{
private:
	int mX, mY;
	bool mStage;		// true: sống, false: chết
	static Figure fig;
	vector<COORD> oldPos;
public:
	People(int x = 0, int y = 0);
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	bool IsImpact(const Obstacle*&);
	bool IsFinish();
	bool IsDead();
	void Print();
	void EraseOld();
	int Width();
	int Height();
};
#endif // !_PEOPLE_H
