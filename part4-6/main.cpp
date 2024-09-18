#include "WeatherData.h"

int main()
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	CDisplay display(&wdIn, &wdOut);
	wdIn.RegisterObserver(display, 5);
	wdOut.RegisterObserver(display, 5);


	wdIn.SetMeasurements(25, 0.4, 760);
	wdOut.SetMeasurements(4, 0.8, 780);


	wdIn.SetMeasurements(10, 0.8, 761);
	wdOut.SetMeasurements(-10, 0.8, 761);
	return 0;
}