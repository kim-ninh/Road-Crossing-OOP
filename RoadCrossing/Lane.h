#pragma once
#ifndef _LANE_H
#define _LANE_H

#include "Obstacle.h"
#include "People.h"

class Lane
{
private:
	int width, heigth;
	COORD pos;
	vector<Obstacle*> obs;
	Direction direc;
public:
	Lane();
	Lane(COORD, vector<Obstacle*>, Direction);
	~Lane();
	COORD GetPos(People&);
	bool IsImpact();
};
#endif // !_LANE_H
