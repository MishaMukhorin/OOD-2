#include "WeatherData.h"

int main()
{
	CWeatherData wd;

    CFishermanDisplay display;
	wd.RegisterObserver(display,EventType::Temperature, 5);
	wd.RegisterObserver(display,EventType::Pressure, 5);


	wd.SetTemp(3);
	wd.SetHumidity(0.8);
	wd.SetPressure(760);

	return 0;
}