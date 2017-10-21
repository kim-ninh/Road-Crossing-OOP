#pragma once
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "Obstacle.h"

class Vehicle : public Obstacle
{
public:
	Vehicle();
	Vehicle(Direction);
	Vehicle(int, int);
	Vehicle(int, int, Direction);
};



#endif // !_VEHICLE_H
