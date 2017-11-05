#include "TrafficLight.h"

TrafficLight::TrafficLight()
{
	countDown = RED_LIGHT_WAITING;
	isRedLightActivated = false;
	warningStatus = false;
	countingTime = 0;
	blink = false;
}

void TrafficLight::Set(char sleep_time)
{
	delayTime = sleep_time;
}

void TrafficLight::print(short x, short y)
{
	if (this->delayTime == 0)
		return;

	GotoXY(x, y);
	if (isRedLightActivated == true)
	{
		if (warningStatus == false)
			TextColor(BACKGROUND_LIGHTRED);
		else
		{
			if (blink == true)
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
			if (blink == true)
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
	if (countingTime == 1000 && countDown > 2000)
	{
		countingTime = 0;
		countDown -= 1000;
	}

	if (countDown == 2000)
	{
		warningStatus = true;
		blink = true;
	}

	if (countingTime == 500 && warningStatus == true)
	{
		countingTime = 0;
		countDown -= 500;
		blink = !blink;
	}

	if (countDown == 0 && isRedLightActivated == false)
	{
		isRedLightActivated = true;
		countDown = GREEN_LIGHT_WAITING;
		warningStatus = false;
	}
	else if (countDown == 0 && isRedLightActivated == true)
	{
		isRedLightActivated = false;
		countDown = RED_LIGHT_WAITING;
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
