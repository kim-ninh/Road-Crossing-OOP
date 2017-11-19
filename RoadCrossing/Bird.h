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
	const Figure& GetFigure() override;
	const char * GetSoundFileName() override;
	Obstacle * Clone(int, int) override;
	ObstacleType GetType() override;
};


#endif // !_BIRD_H
