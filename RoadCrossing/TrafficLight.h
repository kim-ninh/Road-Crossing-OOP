#pragma once
#ifndef _TRAFFICLIGHT_H
#define _TRAFFICLIGHT_H
#define RED_LIGHT_WAITING 5 * 1000		//3 sec
#define GREEN_LIGHT_WAITING 3 * 1000	//5 sec

#include"Console.h"

class TrafficLight {
private:
	short countDown;
	short countingTime;
	bool isRedLightActivated;
	bool warningStatus, blink;
	short delayTime;
public:

	TrafficLight();
	void Set(char sleep_time);
	void print(short x, short y);
	void updateTimeNum();
	void trafficAnimation(short x, short y);
	bool isRedActivated();
};

#endif