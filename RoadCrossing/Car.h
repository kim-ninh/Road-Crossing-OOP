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
	Car(int, int, Direction);
	const Figure& GetFigure() override;
	const char * GetSoundFileName() override;
	Obstacle * Clone(int, int) override;
	ObstacleType GetType() override;
};


#endif // !_CAR_H
