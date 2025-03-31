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
