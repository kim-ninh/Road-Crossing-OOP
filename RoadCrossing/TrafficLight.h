#pragma once
#ifndef _TRAFFICLIGHT_H
#define _TRAFFICLIGHT_H
#define RED_LIGHT_WAITING 3 * 1000		//Tổng thời gian của đèn xanh
#define GREEN_LIGHT_WAITING 2 * 1000	//Tổng thời gian của đèn đỏ
#define TIME_BLINKING 2000				//giây bắt đầu nhấp nháy
#define ONE_SECOND 1000		//do ảnh hưởng hàm Sleep() bên ngoài tính theo đv (mili giây)

#include"Console.h"

class TrafficLight {
private:
	short countDown;
	short countingTime;
	bool isRedLightActivated;
	bool warningStatus, blinking;
	short delayTime;
public:

	TrafficLight();
	TrafficLight(char sleep_time, bool redLightBegin);
	void Set(char sleep_time);
	void print(short x, short y);
	void updateTimeNum();
	void trafficAnimation(short x, short y);
	bool isRedActivated();
};

#endif