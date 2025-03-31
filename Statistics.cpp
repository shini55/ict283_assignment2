// statistics.cpp
#include "Statistics.h"
#include <cmath>



float Statistics::calculateAverage(int avgType, int year, int month,
                                   const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData,
                                   const Map<int, Map<int, BinarySearchTree<int>>>& weatherValues) const {
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) {
        return 0.0f; // Return 0 if no data for the given year and month
    }

    float totalValue = 0.0f;
    int totalNumOfData = 0;

    Vector<WeatherRecType> currentMonthData = weatherData.get(year).get(month);

    for (int i = 0; i < currentMonthData.GetSize(); ++i) {
        switch (avgType) {
            case 0: // Average speed
                totalValue += currentMonthData[i].GetSpeed();
                break;
            case 1: // Average temperature
                totalValue += currentMonthData[i].GetTemperature();
                break;
            case 2: // Average solar radiation
                totalValue += currentMonthData[i].GetSolarRadiation();
                break;
            default:
                return 0.0f; // Return 0 for invalid avgType
        }
        totalNumOfData++;
    }

    if (totalNumOfData == 0) {
        return 0.0f; // Return 0 if no data for the given year and month
    }

    if (avgType == 0) {
        return (totalValue / totalNumOfData) * 3.6f; // Convert speed to km/h
    } else {
        return totalValue / totalNumOfData;
    }
}
float Statistics::calculateStandardDeviation(int stdDeviationType, int year, int month,
                                             const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData,
                                             const Map<int, Map<int, BinarySearchTree<int>>>& weatherValues) const {
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) {
        return 0.0f;
    }

    float sumSquaredDiff = 0.0f;
    int totalNumOfData = 0;
    float average = 0.0f;

    Vector<WeatherRecType> currentMonthData = weatherData.get(year).get(month);

    if (currentMonthData.GetSize() == 0) {
        return 0.0f; // No data, standard deviation is 0
    }

    // Calculate the average first
    average = calculateAverage(stdDeviationType, year, month, weatherData, weatherValues);

    // Calculate the sum of squared differences
    for (int i = 0; i < currentMonthData.GetSize(); ++i) {
        float value;
        switch (stdDeviationType) {
            case 0: // Speed
                value = currentMonthData[i].GetSpeed();
                break;
            case 1: // Temperature
                value = currentMonthData[i].GetTemperature();
                break;
            default:
                return 0.0f; // Invalid stdDeviationType
        }
        float diff = value - average;
        sumSquaredDiff += diff * diff;
        totalNumOfData++;
    }

    // Calculate the standard deviation
    if (totalNumOfData <= 1) {
        return 0.0f; // Standard deviation is undefined for 0 or 1 data points
    }

    return sqrt(sumSquaredDiff / (totalNumOfData - 1));
}

float Statistics::calculateTotalSolarRadiation(int year, int month,
                                               const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData,
                                               const Map<int, Map<int, BinarySearchTree<int>>>& weatherValues) const {
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) return 0.0f;

    float totalSolarRadiationkWh = 0.0f;
    float timeIntervalHours = 1.0f / 6.0f; // Replace with your correct time interval in hours

    Vector<WeatherRecType> currentMonthData = weatherData.get(year).get(month);

    for (int i = 0; i < currentMonthData.GetSize(); ++i) {
        float solarRadiationWm2 = currentMonthData[i].GetSolarRadiation();

        if (solarRadiationWm2 >= 100.0f) {
            float solarRadiationkWhm2 = (solarRadiationWm2 * timeIntervalHours) / 1000.0f;
            totalSolarRadiationkWh += solarRadiationkWhm2;
        }
    }

    return totalSolarRadiationkWh;
}

float Statistics::calculateSPCC(int month, int combination, const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData) const {
    Vector<float> xValues, yValues;

    // Iterate through the years using the map's has and get methods
    int yearKeys[100]; // Assuming a maximum of 100 years, adjust as needed.
    int yearKeyCount = 0;

    for (int year = 0; year < 3000; ++year) { // Adjust the upper limit as needed.
        if (weatherData.has(year)) {
            yearKeys[yearKeyCount] = year;
            yearKeyCount++;
        }
    }

    for (int yearIndex = 0; yearIndex < yearKeyCount; ++yearIndex) {
        int year = yearKeys[yearIndex];
        if (weatherData.get(year).has(month)) {
            Vector<WeatherRecType> monthData = weatherData.get(year).get(month);

            for (int dataIndex = 0; dataIndex < monthData.GetSize(); ++dataIndex) {
                float x = 0.0f, y = 0.0f;

                switch (combination) {
                    case 0: // S_T
                        x = monthData[dataIndex].GetSpeed();
                        y = monthData[dataIndex].GetTemperature();
                        break;
                    case 1: // S_R
                        x = monthData[dataIndex].GetSpeed();
                        y = monthData[dataIndex].GetSolarRadiation();
                        break;
                    case 2: // T_R
                        x = monthData[dataIndex].GetTemperature();
                        y = monthData[dataIndex].GetSolarRadiation();
                        break;
                    default:
                        return 0.0f; // Invalid combination
                }

                xValues.Insert(x, xValues.GetSize());
                yValues.Insert(y, yValues.GetSize());
            }
        }
    }

    if (xValues.GetSize() < 2) {
        return 0.0f; // Not enough data for correlation
    }

    float sumX = 0.0f, sumY = 0.0f, sumXY = 0.0f, sumX2 = 0.0f, sumY2 = 0.0f;
    int n = xValues.GetSize();

    for (int i = 0; i < n; ++i) {
        sumX += xValues[i];
        sumY += yValues[i];
        sumXY += xValues[i] * yValues[i];
        sumX2 += xValues[i] * xValues[i];
        sumY2 += yValues[i] * yValues[i];
    }

    float numerator = n * sumXY - sumX * sumY;
    float denominator = sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

    if (denominator == 0.0f) {
        return 0.0f; // Prevent division by zero
    }

    return numerator / denominator;
}


float Statistics::calculateMAD(int madType, int year, int month,
                                const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData) const {
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) {
        return 0.0f;
    }

    Vector<WeatherRecType> monthData = weatherData.get(year).get(month);
    int totalNumOfData = monthData.GetSize();

    if (totalNumOfData == 0) {
        return 0.0f;
    }

    float average = 0.0f;
    Vector<float> values;

    for (int i = 0; i < totalNumOfData; ++i) {
        if (madType == 0) { // Speed
            values.Insert(monthData[i].GetSpeed(), values.GetSize());
            average += monthData[i].GetSpeed();
        } else if (madType == 1) { // Temperature
            values.Insert(monthData[i].GetTemperature(), values.GetSize());
            average += monthData[i].GetTemperature();
        }
    }
    average /= totalNumOfData;

    float sumAbsDiff = 0.0f;

    for (int i = 0; i < totalNumOfData; ++i) {
        float diff = values[i] - average;
        if (diff < 0.0f) {
            sumAbsDiff += -diff;
        } else {
            sumAbsDiff += diff;
        }
    }

    // Return the calculated MAD
    return sumAbsDiff / totalNumOfData;
}
