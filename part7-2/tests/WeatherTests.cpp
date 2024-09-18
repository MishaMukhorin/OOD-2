#include "../WeatherData.h"
#include <gtest/gtest.h>

class SelfRemovingObserver : public IObserver<SWeatherInfo>
{
public:

    SelfRemovingObserver(CObservable<SWeatherInfo>& observable): m_observable(observable)
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
TEST(ObserverTests, TestRemoveObserverDuringNotify)
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


// Класс-наблюдатель для тестирования приоритета
class PriorityObserver : public IObserver<SWeatherInfo>
{
public:
    PriorityObserver(int id, std::vector<int>& callOrder)
            : m_id(id), m_callOrder(callOrder)
    {
    }

    void Update(SWeatherInfo const& data) override
    {
        m_callOrder.push_back(m_id);  // Добавляем идентификатор наблюдателя в порядок вызова
    }

private:
    int m_id;
    std::vector<int>& m_callOrder;
};
// Тест на проверку работы приоритета наблюдателей, включая отрицательные кейсы
TEST(WeatherStationTest, ObserverPriorityTest)
{
    CWeatherData wd;

    std::vector<int> callOrder;

    PriorityObserver highPriorityObserver(1, callOrder);
    PriorityObserver lowPriorityObserver(2, callOrder);

    wd.RegisterObserver(lowPriorityObserver, 1);
    wd.RegisterObserver(highPriorityObserver, 2);

    wd.SetMeasurements(10, 0.8, 761);

    ASSERT_EQ(callOrder.size(), 2);

    // Проверяем, что высокий приоритет вызвался первым
    EXPECT_LT(callOrder[0], callOrder[1]) << "High-priority observer should be called before low-priority observer";
}


GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
