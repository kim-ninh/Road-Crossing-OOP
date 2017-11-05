#pragma once
#include "Bird.h"

char* Bird::sSoundFileName = "Sound\\Bird.wav";
Figure Bird::figLeft("Figure\\Bird_Left.txt");
Figure Bird::figRight("Figure\\Bird_Right.txt");

Bird::Bird() {}

Bird::Bird(Direction theDirec) : Animal(theDirec) {}

Bird::Bird(int x, int y) : Animal(x,y) {}

Bird::Bird(int x, int y, Direction theDirec) : Animal(x, y, theDirec) {}

const Figure & Bird::GetFigure()
{
	if (direc == LEFT) {
		return figLeft;
	}
	else {
		return figRight;
	}
}

const char * Bird::GetSoundFileName()
{
	return sSoundFileName;
}

Obstacle * Bird::Clone(int x, int y)
{
	return new Bird(x, y, direc);
}

ObstacleType Bird::GetType()
{
	return BIRD;
}
