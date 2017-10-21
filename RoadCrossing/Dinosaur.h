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
	const Figure& GetFigure();
	const char * GetSoundFileName();
	Obstacle * Clone(int, int);
};


#endif // !_DINOSAUR_H
