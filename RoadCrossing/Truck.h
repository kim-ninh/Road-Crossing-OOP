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
	const Figure& GetFigure();
	const char * GetSoundFileName();
};


#endif // !_TRUCK_H
