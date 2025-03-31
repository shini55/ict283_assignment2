#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "Vector.h"
#include "Map.h"
#include "BinarySearchTree.h"
#include <cmath>
#include "WeatherRecType.h" // Include WeatherRecType.h

class Statistics {
public:
    float calculateAverage(int avgType, int year, int month,
                            const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData,
                            const Map<int, Map<int, BinarySearchTree<int>>>& weatherValues) const;

    float calculateStandardDeviation(int stdDeviationType, int year, int month,
                                     const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData,
                                     const Map<int, Map<int, BinarySearchTree<int>>>& weatherValues) const;

    float calculateTotalSolarRadiation(int year, int month,
                                       const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData,
                                       const Map<int, Map<int, BinarySearchTree<int>>>& weatherValues) const;

     float calculateSPCC(int month, int combination, const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData) const;


     float calculateMAD(int madType, int year, int month,
                                const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData) const;


};
#endif // STATISTICS_H_INCLUDED
