// statistics.cpp
#include "Statistics.h"
#include <cmath>



Statistics::Statistics(const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData):weatherData(weatherData)
{
    populateValidData();
}

void Statistics::populateValidData()
{

    for (int year = 1999; year <= 2100; ++year)
    {
        if (weatherData.has(year))
        {
            validYears.Insert(year);

            // Scan through possible months (1-12)
            for (int month = 1; month <= 12; ++month)
            {
                if (weatherData.get(year).has(month))
                {
                    validMonths.Insert(month);
                }
            }
        }
    }
}

bool Statistics::isValidData(int year, int month) const
{

    if (!validYears.Search(year) || !validMonths.Search(month))
    {
        return false;
    }

    // Then verify exact year-month combination exists
    return weatherData.has(year) && weatherData.get(year).has(month);
}


float Statistics::calculateAverage(int avgType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0;
    }

    const Vector<WeatherRecType>& monthRecords = weatherData.get(year).get(month);
    float totalSpeed = 0.0, totalTemperature = 0.0, totalSolarRadiation = 0.0;
    int totalNumOfData = monthRecords.GetSize();

    if (totalNumOfData == 0)
    {
        return 0.0;
    }

    for (int i = 0; i < totalNumOfData; ++i)
    {
        totalSpeed += monthRecords[i].GetSpeed();
        totalTemperature += monthRecords[i].GetTemperature();
        totalSolarRadiation += monthRecords[i].GetSolarRadiation();
    }

    switch (avgType)
    {
    case 0:
        return (totalSpeed / totalNumOfData) * 3.6;
    case 1:
        return totalTemperature / totalNumOfData;
    case 2:
        return totalSolarRadiation / totalNumOfData;
    default:
        return 0.0;
    }
}

float Statistics::calculateStandardDeviation(int stdDeviationType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0;
    }

    float sumSpeed = 0.0;
    float sumTemperature = 0.0;
    int totalNumOfData = 0;

    float avgSpeed = calculateAverage(0, year, month);
    float avgTemperature = calculateAverage(1, year, month);

    const Vector<WeatherRecType>& monthRecords = weatherData.get(year).get(month);
    for (int i = 0; i < monthRecords.GetSize(); i++)
    {
        float speedDiff = monthRecords[i].GetSpeed() - avgSpeed;
        sumSpeed += speedDiff * speedDiff;

        float tempDiff = monthRecords[i].GetTemperature() - avgTemperature;
        sumTemperature += tempDiff * tempDiff;

        totalNumOfData++;
    }

    if (totalNumOfData <= 1)
    {
        return 0.0;
    }

    switch (stdDeviationType)
    {
    case 0:
        return sqrt(sumSpeed / (totalNumOfData - 1));
    case 1:
        return sqrt(sumTemperature / (totalNumOfData - 1));
    default:
        return 0.0;
    }
}

float Statistics::calculateTotalSolarRadiation(int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0f;
    }

    float totalSolarRadiationkWh = 0.0f;
    const Vector<WeatherRecType>& monthRecords = weatherData.get(year).get(month);

    for (int i = 0; i < monthRecords.GetSize(); ++i)
    {
        float solarRadiationWm2 = monthRecords[i].GetSolarRadiation();
        if (solarRadiationWm2 >= 100.0f)
        {
            float solarRadiationkWhm2 = (solarRadiationWm2 * (1.0f / 6.0f)) / 1000.0f;
            totalSolarRadiationkWh += solarRadiationkWhm2;
        }
    }

    return totalSolarRadiationkWh;
}

float Statistics::calculateSPCC(int combinationType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0f;
    }

    Vector<float> xValues, yValues;
    const Vector<WeatherRecType>& monthData = weatherData.get(year).get(month);

    for (int i = 0; i < monthData.GetSize(); ++i)
    {
        float x = 0.0f, y = 0.0f;
        switch (combinationType)
        {
        case 0:
            x = monthData[i].GetSpeed();
            y = monthData[i].GetTemperature();
            break;
        case 1:
            x = monthData[i].GetSpeed();
            y = monthData[i].GetSolarRadiation();
            break;
        case 2:
            x = monthData[i].GetTemperature();
            y = monthData[i].GetSolarRadiation();
            break;
        default:
            return 0.0f;
        }
        xValues.Insert(x, xValues.GetSize());
        yValues.Insert(y, yValues.GetSize());
    }

    if (xValues.GetSize() != yValues.GetSize() || xValues.GetSize() == 0)
    {
        return 0.0f;
    }

    float sumX = 0.0f, sumY = 0.0f, sumXY = 0.0f;
    float sumX2 = 0.0f, sumY2 = 0.0f;
    int n = xValues.GetSize();

    for (int i = 0; i < n; ++i)
    {
        sumX += xValues[i];
        sumY += yValues[i];
        sumXY += xValues[i] * yValues[i];
        sumX2 += xValues[i] * xValues[i];
        sumY2 += yValues[i] * yValues[i];
    }

    float numerator = sumXY - (sumX * sumY / n);
    float denominator = sqrt((sumX2 - (sumX * sumX / n)) * (sumY2 - (sumY * sumY / n)));

    if (denominator == 0.0f)
    {
        return 0.0f;
    }

    return numerator / denominator;
}

float Statistics::calculateMAD(int madType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0f;
    }

    Vector<float> values;
    const Vector<WeatherRecType>& records = weatherData.get(year).get(month);

    float sum = 0.0f;
    for (int i = 0; i < records.GetSize(); ++i)
    {
        float value = 0.0f;
        switch (madType)
        {
        case 0:
            value = records[i].GetSpeed();
            break;
        case 1:
            value = records[i].GetTemperature();
            break;
        default:
            return 0.0f;
        }
        values.Insert(value, values.GetSize());
        sum += value;
    }

    if (values.GetSize() == 0)
    {
        return 0.0f;
    }

    float average = sum / values.GetSize();
    float sumDeviations = 0.0f;

    for (int i = 0; i < values.GetSize(); ++i)
    {
        sumDeviations += fabs(values[i] - average);
    }

    return sumDeviations / values.GetSize();
}

