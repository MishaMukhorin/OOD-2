

#include "WeatherData.h"


class SelfRemovingObserver : public IObserver<SWeatherInfo>
{
public:
    SelfRemovingObserver(CObservable<SWeatherInfo>& observable)
            : m_observable(observable)
    {
    }

    void Update(SWeatherInfo const& data) override
    {
        std::cout << "SelfRemovingObserver received update. Removing itself." << std::endl;
        m_observable.RemoveObserver(*this);
    }

private:
    CObservable<SWeatherInfo>& m_observable;
};

void TestRemoveObserverDuringNotify()
{
    CWeatherData wd;

    CDisplay display1;
    wd.RegisterObserver(display1);

    SelfRemovingObserver selfRemovingObserver(wd);
    wd.RegisterObserver(selfRemovingObserver);

    std::cout << "First measurement update:" << std::endl;
    wd.SetMeasurements(10, 0.8, 761);

    std::cout << "Second measurement update:" << std::endl;
    wd.SetMeasurements(15, 0.6, 765);
}



