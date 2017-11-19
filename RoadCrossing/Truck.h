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
	const Figure& GetFigure() override;
	const char * GetSoundFileName() override;
	Obstacle * Clone(int, int) override;
	ObstacleType GetType() override;
};


#endif // !_TRUCK_H
