#include "../WeatherData.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>




// Мок-объект для тестирования отображения данных
class MockDisplay : public IObserver<SWeatherInfo>
{
public:
    MOCK_METHOD(void, Update, (const SWeatherInfo& data, const CObservable<SWeatherInfo>* observable), (override));

    MockDisplay() = default;
};

TEST(WeatherStationDuoTest, CorrectStationSourceTest)
{
    CWeatherData weatherDataIn;
    CWeatherData weatherDataOut;
    MockDisplay mockDisplay;

    weatherDataIn.RegisterObserver(mockDisplay);
    weatherDataOut.RegisterObserver(mockDisplay);

    SWeatherInfo dataIn = {22.5, 0.55, 750.0};
    SWeatherInfo dataOut = {12.0, 0.75, 760.0};

    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataIn)).Times(1);
    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataOut)).Times(1);

    weatherDataIn.SetMeasurements(dataIn.temperature, dataIn.humidity, dataIn.pressure);
    weatherDataOut.SetMeasurements(dataOut.temperature, dataOut.humidity, dataOut.pressure);
}





GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
