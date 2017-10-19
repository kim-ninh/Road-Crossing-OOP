#pragma once
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "Obstacle.h"

class Vehicle : public Obstacle
{
public:
	Vehicle();
	Vehicle(Direction);
	Vehicle(int, int, Direction theDirec = LEFT);
};



#endif // !_VEHICLE_H
