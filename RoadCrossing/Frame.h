#pragma once
#ifndef _FRAME_H
#define _FRAME_H

#include <iostream>
#include "Console.h"

class Frame
{
private:
	short height;
	short width;
	COORD pos;
public:
	Frame();
	Frame(short, short, COORD);

	void Set(short, short, COORD);
	void Draw();
	void Frame::Draw_(char **);
};

#endif // !_FRAME_H
