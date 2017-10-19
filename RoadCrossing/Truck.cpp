#pragma once
#include "Truck.h"

char* Truck::sSoundFileName = "Sound\\Truct.wav";
Figure Truck::figLeft("Figure\\Truck_Left.txt");
Figure Truck::figRight("Figure\\Truck_Right.txt");

Truck::Truck() {}

Truck::Truck(Direction theDirec) : Vehicle(theDirec) {}

Truck::Truck(int x, int y) : Vehicle(x, y) {}

const Figure & Truck::GetFigure()
{
	if (direc == LEFT) {
		return figLeft;
	}
	else {
		return figRight;
	}
}

const char * Truck::GetSoundFileName()
{
	return sSoundFileName;
}