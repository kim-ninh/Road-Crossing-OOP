#pragma once
#include "Car.h"


char* Car::sSoundFileName = "Sound\\Car.wav";
Figure Car::figLeft("Figure\\Car_Left.txt");
Figure Car::figRight("Figure\\Car_Right.txt");

Car::Car() {}

Car::Car(Direction theDirec) : Vehicle(theDirec) {}

Car::Car(int x, int y, Direction theDirec) : Vehicle(x, y, theDirec) {}

const Figure & Car::GetFigure()
{
	if (direc == LEFT) {
		return figLeft;
	}
	else {
		return figRight;
	}
}

const char * Car::GetSoundFileName()
{
	return sSoundFileName;
}

Obstacle * Car::Clone(int x, int y)
{
	return new Car(x, y, direc);
}
