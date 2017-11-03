#pragma once
#ifndef _LANE_H
#define _LANE_H

#include "Obstacle.h"
#include "People.h"

class Lane
{
private:
	int width, height;
	COORD pos;
	vector<Obstacle*> obs;
	Direction direc;
public:
	Lane();
	Lane(COORD, vector<Obstacle*>, Direction);
	~Lane();
	int Height();
	void UpdatePos();
	void Print();
	COORD GetPos(People&);
	COORD GetPos();
	bool IsImpact(People& people);
};
#endif // !_LANE_H
