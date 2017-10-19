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

class Obstacle
{
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
	void EraseOldPos();
	void Print();
};

#endif // !_OBSTACLE_H
