//
// Created by Misha on 12.09.2024.
//

#ifndef OOD_2_CSTATISTICS_H
#define OOD_2_CSTATISTICS_H

#include <limits>

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
