#pragma once
#include "Dinosaur.h"


char* Dinosaur::sSoundFileName = "Sound\\Dinosaur.wav";
Figure Dinosaur::figLeft("Figure\\Dinosaur_Left.txt");
Figure Dinosaur::figRight("Figure\\Dinosaur_Right.txt");

Dinosaur::Dinosaur() {}

Dinosaur::Dinosaur(Direction theDirec) : Animal(theDirec) {}

Dinosaur::Dinosaur(int x, int y) : Animal(x,y) {}

const Figure & Dinosaur::GetFigure()
{
	if (direc == LEFT) {
		return figLeft;
	}
	else {
		return figRight;
	}
}

const char * Dinosaur::GetSoundFileName()
{
	return sSoundFileName;
}
