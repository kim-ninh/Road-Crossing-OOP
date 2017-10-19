#pragma once
#ifndef _CAR_H
#define _CAR_H

#include "Vehicle.h"

class Car : public Vehicle
{
private:
	static char *sSoundFileName;
	static Figure figLeft, figRight;
public:
	Car();
	Car(Direction);
	Car(int, int, Direction theDirec = LEFT);
	const Figure& GetFigure();
	const char * GetSoundFileName();
};


#endif // !_CAR_H
