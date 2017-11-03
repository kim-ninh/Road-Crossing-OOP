#pragma once
#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include <iostream>
#include <mutex>
#include "Figure.h"

using namespace std;

enum Direction {
	LEFT, RIGHT
};

class Lane;

class Obstacle
{
	friend class Lane;
private:
	int mX, mY;
protected:
	short oldX;
	Direction direc;
public:
	Obstacle();
	Obstacle(Direction);
	Obstacle(int, int, Direction theDirec = LEFT);
	void Move();
	void Tell();
	virtual const Figure& GetFigure() = 0;
	virtual const char* GetSoundFileName() = 0;
	int Width();
	int Height();
	void EraseOldPos();
	void Print();
	COORD GetPosition();
	bool IsImpact(People& people);
	void SetPosition(short, short);
	virtual Obstacle * Clone(int, int) = 0;
};

#endif // !_OBSTACLE_H
