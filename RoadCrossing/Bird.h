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
	const Figure& GetFigure();
	const char * GetSoundFileName();
};


#endif // !_BIRD_H
