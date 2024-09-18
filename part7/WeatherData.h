#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include "CStatistics.h"

struct SWeatherInfo
{
    double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class CWeatherData;

class CDisplay: public IObserver<SWeatherInfo>
{
public:
    CDisplay(CObservable<SWeatherInfo>* weatherDataIn, CObservable<SWeatherInfo>* weatherDataOut)
            : m_weatherDataIn(weatherDataIn), m_weatherDataOut(weatherDataOut)
    {
    }

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
	{
        std::string location = (observable == m_weatherDataIn) ? "Inside" :
                               (observable == m_weatherDataOut) ? "Outside" : "Undefined";

		std::cout << "Current Location is " << location << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
    const CObservable<SWeatherInfo> *m_weatherDataIn, *m_weatherDataOut;
};

class CStatsDisplayProDuo : public IObserver<SWeatherInfo>
{
private:
    CStatsDisplayProDuo() = default;

    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
        */
	void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
	{

        std::string location = (observable == m_weatherDataIn) ? "Inside" :
                               (observable == m_weatherDataOut) ? "Outside" : "Undefined";
        if (observable == m_weatherDataIn)
        {
            m_temperatureStatsInside.Update(data.temperature);
            m_humidityStatsInside.Update(data.humidity);
            m_pressureStatsInside.Update(data.pressure);

            std::cout << "Weather Station Inside Stats: " << std::endl;

            std::cout << "Temperature S tats: Max " << m_temperatureStatsInside.GetMax()
                      << ", Min " << m_temperatureStatsInside.GetMin()
                      << ", Avg " << m_temperatureStatsInside.GetAverage() << std::endl;

            std::cout << "Humidity Stats: Max " << m_humidityStatsInside.GetMax()
                      << ", Min " << m_humidityStatsInside.GetMin()
                      << ", Avg " << m_humidityStatsInside.GetAverage() << std::endl;

            std::cout << "Pressure Stats: Max " << m_pressureStatsInside.GetMax()
                      << ", Min " << m_pressureStatsInside.GetMin()
                      << ", Avg " << m_pressureStatsInside.GetAverage() << std::endl;
        }
        else if (observable == m_weatherDataOut)
        {
            m_temperatureStatsOutside.Update(data.temperature);
            m_humidityStatsOutside.Update(data.humidity);
            m_pressureStatsOutside.Update(data.pressure);
            m_windStatsOutside.Update(data.windSpeed, data.windDirection);

            std::cout << "Weather Station Outside Stats: " << std::endl;
            std::cout << "Temperature Stats: Max " << m_temperatureStatsOutside.GetMax()
                      << ", Min " << m_temperatureStatsOutside.GetMin()
                      << ", Avg " << m_temperatureStatsOutside.GetAverage() << std::endl;

            std::cout << "Humidity Stats: Max " << m_humidityStatsOutside.GetMax()
                      << ", Min " << m_humidityStatsOutside.GetMin()
                      << ", Avg " << m_humidityStatsOutside.GetAverage() << std::endl;

            std::cout << "Pressure Stats: Max " << m_pressureStatsOutside.GetMax()
                      << ", Min " << m_pressureStatsOutside.GetMin()
                      << ", Avg " << m_pressureStatsOutside.GetAverage() << std::endl;

            std::cout << "Wind Speed Stats: Max " << m_windStatsOutside.GetMaxSpeed()
                      << ", Min " << m_windStatsOutside.GetMinSpeed()
                      << ", Avg " << m_windStatsOutside.GetAverageSpeed() << std::endl;

            std::cout << "Average Wind Direction: " << m_windStatsOutside.GetAverageDirection()
                      << " degrees" << std::endl;
        }
        else
        {
            std::cout << "Unknown weather station " << std::endl;
        }

        std::cout << "----------------" << std::endl;
    }

    CStatistics m_temperatureStatsInside, m_humidityStatsInside, m_pressureStatsInside;
    CStatistics m_temperatureStatsOutside, m_humidityStatsOutside, m_pressureStatsOutside;
    CWindStats m_windStatsOutside;

    const CObservable<SWeatherInfo> *m_weatherDataIn{}, *m_weatherDataOut{};

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
    CWeatherData() = default;

    // Температура в градусах Цельсия
	[[nodiscard]] double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	[[nodiscard]] double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	[[nodiscard]] double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	[[nodiscard]] SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
