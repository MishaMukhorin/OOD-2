#ifndef OOD_2_CSTATISTICS_H
#define OOD_2_CSTATISTICS_H

#include <limits>
#include <cmath>

class CWindStats
{
public:
    void Update(double speed, double direction)
    {
        if (m_minSpeed > speed)
        {
            m_minSpeed = speed;
        }
        if (m_maxSpeed < speed)
        {
            m_maxSpeed = speed;
        }
        double radianDirection = direction * M_PI / 180.0;

        double x = speed * cos(radianDirection);
        double y = speed * sin(radianDirection);

        m_sumX += x;
        m_sumY += y;
        m_totalSpeed += speed;
        ++m_count;
    }

    double GetMinSpeed() const
    {
        return m_minSpeed;
    }

    // Получить максимальную скорость
    double GetMaxSpeed() const
    {
        return m_maxSpeed;
    }

    [[nodiscard]] double GetAverageDirection() const
    {
        if (m_count == 0)
        {
            return 0;
        }

        double averageDirection = atan2(m_sumY / m_count, m_sumX / m_count) * 180.0 / M_PI;
        return fmod(averageDirection + 360.0, 360.0);
    }

    [[nodiscard]] double GetAverageSpeed() const
    {
        return (m_count != 0) ? m_totalSpeed / m_count : 0;
    }

private:
    double m_sumX = 0.0;
    double m_sumY = 0.0;
    double m_totalSpeed = 0.0;
    unsigned m_count = 0;
    double m_minSpeed = std::numeric_limits<double>::infinity();
    double m_maxSpeed = -std::numeric_limits<double>::infinity();

};


class CStatistics
{
public:
    void Update(double value)
    {
        if (m_min > value)
        {
            m_min = value;
        }
        if (m_max < value)
        {
            m_max = value;
        }
        m_acc += value;
        ++m_count;
    }

    [[nodiscard]] double GetMin() const { return m_min; }
    [[nodiscard]] double GetMax() const { return m_max; }
    [[nodiscard]] double GetAverage() const { return (m_count != 0) ? m_acc / m_count : 0; }

private:
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_acc = 0;
    unsigned m_count = 0;
};

#endif //OOD_2_CSTATISTICS_H
