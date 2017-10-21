#pragma once
#include "Vehicle.h"

Vehicle::Vehicle() {}

Vehicle::Vehicle(Direction theDirec) : Obstacle(theDirec) {}

Vehicle::Vehicle(int x, int y) : Obstacle(x,y) {}

Vehicle::Vehicle(int x, int y, Direction theDirec) : Obstacle(x, y, theDirec) {}