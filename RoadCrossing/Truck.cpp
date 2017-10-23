
#include "Truck.h"

Figure Truck::figLeft("Figure\\Truck_Left.txt");
Figure Truck::figRight("Figure\\Truck_Right.txt");
char* Truck::sSoundFileName = "Sound\\Truck.wav";

Truck::Truck() {}

Truck::Truck(Direction theDirec) : Vehicle(theDirec) {}

Truck::Truck(int x, int y) : Vehicle(x, y) {}

Truck::Truck(int x, int y, Direction theDirec) : Vehicle(x, y, theDirec)
{
#ifndef TRUCK_FIGURE
#define TRUCK_FIGURE
	figLeft = Figure("Figure\\Truck_Left.txt");
	figRight = Figure("Figure\\Truck_Right.txt");
#endif // !TRUCK_FIGURE
}

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

Obstacle * Truck::Clone(int x, int y)
{
	return new Truck(x, y, direc);
}