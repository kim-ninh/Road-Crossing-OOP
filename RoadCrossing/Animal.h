#pragma once
#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "Obstacle.h"

class Animal abstract : public Obstacle
{
public:
	Animal();
	Animal(Direction);
	Animal(int, int);
	Animal(int, int, Direction);
};


#endif // !_ANIMAL_H
