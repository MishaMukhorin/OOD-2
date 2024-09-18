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
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplayProDuo : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
        m_temperatureStats.Update(data.temperature);
        m_humidityStats.Update(data.humidity);
        m_pressureStats.Update(data.pressure);

        std::cout << "Temperature Stats: Max " << m_temperatureStats.GetMax()
                  << ", Min " << m_temperatureStats.GetMin()
                  << ", Avg " << m_temperatureStats.GetAverage() << std::endl;

        std::cout << "Humidity Stats: Max " << m_humidityStats.GetMax()
                  << ", Min " << m_humidityStats.GetMin()
                  << ", Avg " << m_humidityStats.GetAverage() << std::endl;

        std::cout << "Pressure Stats: Max " << m_pressureStats.GetMax()
                  << ", Min " << m_pressureStats.GetMin()
                  << ", Avg " << m_pressureStats.GetAverage() << std::endl;

        std::cout << "----------------" << std::endl;
    }

    CStatistics m_temperatureStats;
    CStatistics m_humidityStats;
    CStatistics m_pressureStats;

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
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
	[[nodiscard]] SWeatherInfo GetChangedData() const override
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
