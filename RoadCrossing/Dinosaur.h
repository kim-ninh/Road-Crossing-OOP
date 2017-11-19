#pragma once
#ifndef _DINOSAUR_H
#define _DINOSAUR_H

#include "Animal.h"

class Dinosaur : public Animal
{
private:
	static char *sSoundFileName;
	static Figure figLeft, figRight;
public:
	Dinosaur();
	Dinosaur(Direction);
	Dinosaur(int, int);
	Dinosaur(int, int, Direction);
	const Figure& GetFigure() override;
	const char * GetSoundFileName() override;
	Obstacle * Clone(int, int) override;
	ObstacleType GetType() override;
};


#endif // !_DINOSAUR_H
