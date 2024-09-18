#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include "CStatistics.h"



struct SWeatherInfoPro
{
	double temperature = 0;
	double pressure = 0;
};

struct SWeatherInfo
{
	double temperature = 0;
    double humidity = 0;
	double pressure = 0;
};

class CFishermanDisplay : public IObserver<SWeatherInfo>
{
private:
    void Update(SWeatherInfo const& data, EventType eventType) override
    {
        if (eventType == EventType::Temperature)
        {
            std::cout << "Current Temperature: " << data.temperature << " C" << std::endl;
        }
        else if (eventType == EventType::Pressure)
        {
            std::cout << "Current Pressure: " << data.pressure << " mm Hg" << std::endl;
        }
    }
};


class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	[[nodiscard]] double GetTemperature()const
	{
		return m_temperature;
	}

	[[nodiscard]] double GetHumidity()const
	{
		return m_humidity;
	}

	[[nodiscard]] double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged(EventType eventType)
	{
		NotifyObservers(eventType);
	}

	void SetTemp(double temp)
	{
		m_temperature = temp;
		MeasurementsChanged(EventType::Temperature);
	}
	void SetPressure(double pressure)
	{
		m_pressure = pressure;

		MeasurementsChanged(EventType::Pressure);
	}
    void SetHumidity(double humidity)
    {
        m_pressure = humidity;

        MeasurementsChanged(EventType::Humidity);
    }

    void SetMeasurements(double temp, double humidity, double pressure)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;

        MeasurementsChanged(EventType::Temperature);
        MeasurementsChanged(EventType::Pressure);
        MeasurementsChanged(EventType::Humidity);
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
	double m_temperature = 10.0;
	double m_humidity = 0.50;
	double m_pressure = 760.0;
};
