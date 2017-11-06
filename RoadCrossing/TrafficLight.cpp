#include "TrafficLight.h"

TrafficLight::TrafficLight()
{
}

TrafficLight::TrafficLight(char sleep_time, bool redLightBegin = false)
{
	countDown = redLightBegin == false ? RED_LIGHT_WAITING : GREEN_LIGHT_WAITING;
	isRedLightActivated = redLightBegin;
	warningStatus = false;
	countingTime = 0;
	blinking = false;
	Set(sleep_time);
}

void TrafficLight::Set(char sleep_time)
{
	delayTime = sleep_time;
}

void TrafficLight::print(short x, short y)
{
	GotoXY(x, y);
	if (isRedLightActivated == true)
	{
		if (warningStatus == false)
			TextColor(BACKGROUND_LIGHTRED);
		else
		{
			if (blinking == true)
				TextColor(BACKGROUND_RED);
			else
				TextColor(BACKGROUND_LIGHTRED);
		}
		putchar(32);
	}
	else
	{
		if (warningStatus == false)
			TextColor(BACKGROUND_LIGHTGREEN);
		else
		{
			if (blinking == true)
				TextColor(BACKGROUND_GREEN);
			else
				TextColor(BACKGROUND_LIGHTGREEN);
		}
		putchar(32);
	}
	TextColor(FOREGROUND_WHITE);			//Trả lại màu nền hệ thống
}

void TrafficLight::updateTimeNum()
{
	if (countingTime == ONE_SECOND && countDown > TIME_BLINKING)
	{
		countDown -= countingTime;
		countingTime = 0;
	}

	if (countDown == TIME_BLINKING)
	{
		warningStatus = true;
		blinking = true;
	}

	if (countingTime == ONE_SECOND/2 && warningStatus == true)
	{
		countDown -= countingTime;
		countingTime = 0;
		blinking = !blinking;
	}

	if (countDown == 0)
	{
		countDown = isRedLightActivated == true ? RED_LIGHT_WAITING : GREEN_LIGHT_WAITING;
		isRedLightActivated = !isRedLightActivated;
		warningStatus = false;
	}

	countingTime += delayTime;
}

void TrafficLight::trafficAnimation(short x, short y)
{

	while (true)
	{
		print(x, y);
		updateTimeNum();
		Sleep(delayTime);
	}
}

bool TrafficLight::isRedActivated()
{
	return isRedLightActivated;
}
