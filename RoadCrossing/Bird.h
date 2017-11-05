#pragma once
#ifndef _BIRD_H
#define _BIRD_H

#include "Animal.h"

class Bird : public Animal
{
private:
	static char *sSoundFileName;
	static Figure figLeft, figRight;
public:
	Bird();
	Bird(Direction);
	Bird(int, int);
	Bird(int, int, Direction);
	const Figure& GetFigure();
	const char * GetSoundFileName();
	Obstacle * Clone(int, int);
	ObstacleType GetType();
};


#endif // !_BIRD_H
