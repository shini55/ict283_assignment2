#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "WeatherLogType.h"
#include "BinarySearchTree.h"
#include "Map.h"
#include <cmath>

class Statistics {
public:
    Statistics(const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData);

    float calculateAverage(int avgType, int year, int month) const;
    float calculateStandardDeviation(int stdDeviationType, int year, int month) const;
    float calculateTotalSolarRadiation(int year, int month) const;
    float calculateSPCC(int combinationType, int year, int month) const;
    float calculateMAD(int madType, int year, int month) const;

private:
    const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData;
    BinarySearchTree<int> validYears;
    BinarySearchTree<int> validMonths;

    void populateValidData();
    bool isValidData(int year, int month) const;


};
#endif // STATISTICS_H_INCLUDED
