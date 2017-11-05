#pragma once
#ifndef _LANE_H
#define _LANE_H

#include "Obstacle.h"
#include "People.h"
#include "Bird.h"
#include "Car.h"
#include "Dinosaur.h"
#include "Truck.h"
#include "TrafficLight.h"

class Lane
{
public:
	int width, height;
	COORD pos;
	vector<Obstacle*> obs;
	TrafficLight *light;
	Direction direc;
	short sleepTime;
	short timeCount;
	short soundWaiting;
public:
	Lane();
	Lane(COORD, vector<Obstacle*>, Direction, short, short);
	~Lane();
	int Height();
	void UpdatePos();
	void Print();
	void Tell(People &);
	COORD GetPos(People&);
	COORD GetPos();
	bool IsImpact(People& people);
	void Write(ostream& outDev);
	void Read(istream& inDev);
	void Deallocate();
	bool IsInside(People &);
};
#endif // !_LANE_H
