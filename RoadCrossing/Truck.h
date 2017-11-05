#pragma once
#ifndef _TRUCK_H
#define _TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle
{
private:
	static char *sSoundFileName;
	static Figure figLeft, figRight;
public:
	Truck();
	Truck(Direction);
	Truck(int, int);
	Truck(int, int, Direction);
	const Figure& GetFigure();
	const char * GetSoundFileName();
	Obstacle * Clone(int, int);
	ObstacleType GetType();
};


#endif // !_TRUCK_H
