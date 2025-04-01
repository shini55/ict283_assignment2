#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "WeatherLogType.h"
#include "BinarySearchTree.h"
#include "Map.h"
#include <cmath>

/**
 * @brief Class for performing statistical calculations on weather data.
 *
 * This class provides methods to calculate various statistics such as average, standard deviation, total solar radiation, SPCC, and MAD (Mean Absolute Deviation) for weather data based on the given year and month.
 */

class Statistics
{
public:

    /**
      * @brief Constructor that initializes the Statistics object with weather data.
      *
      * @param weatherData A reference to the weather data map, organized by year and month.
      */
    Statistics(const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData);

    /**
    * @brief Calculates the average for a specific weather measurement.
    *
    * @param avgType Type of measurement
    * @param year Year of the data.
    * @param month Month of the data.
    * @return The calculated average for the given measurement.
    */
    float calculateAverage(int avgType, int year, int month) const;

    /**
     * @brief Calculates the standard deviation for a specific weather measurement.
     *
     * @param stdDeviationType Type of measurement
     * @param year Year of the data.
     * @param month Month of the data.
     * @return The calculated standard deviation for the given measurement.
     */
    float calculateStandardDeviation(int stdDeviationType, int year, int month) const;

    /**
     * @brief Calculates the total solar radiation for a specific month and year.
     *
     * @param year Year of the data.
     * @param month Month of the data.
     * @return The total solar radiation for the given year and month.
     */
    float calculateTotalSolarRadiation(int year, int month) const;

    /**
     * @brief Calculates the Solar Power Conversion Coefficient
     *
     * @param combinationType Type of SPCC calculation.
     * @param year Year of the data.
     * @param month Month of the data.
     * @return The calculated SPCC for the given year and month.
     */
    float calculateSPCC(int combinationType, int year, int month) const;

    /**
    * @brief Calculates the mean (average) of a list of numbers.
    *
    * @param values List of numbers to calculate the mean.
    * @return The mean value.
    */
    float calculateMeanForSPCCandMAD(const Vector<float>& values) const;

    /**
     * @brief Calculates the standard deviation of a list of numbers.
     *
     * @param values List of numbers to calculate the standard deviation.
     * @param mean The mean value of the numbers.
     * @return The standard deviation value.
     */
    float calculateStandardDeviationForSPCC(const Vector<float>& values, float mean) const;





    /**
    * @brief Calculates the Mean Absolute Deviation  for a weather measurement.
    *
    * @param madType Type of measurement
    * @param year Year of the data.
    * @param month Month of the data.
    * @return The MAD value for the given measurement.
    */
    float calculateMAD(int madType, int year, int month) const;



private:
    const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData; ///Reference to the weather data map, organized by year and month.
    BinarySearchTree<int> validYears; ///Binary search tree containing valid years.
    BinarySearchTree<int> validMonths;///Binary search tree containing valid months.

    /**
     * @brief Populates the valid years and months from the weather data.
     */
    void populateValidData();

    /**
    * @brief Checks if the data for a specific year and month is valid.
    *
    * @param year Year to check.
    * @param month Month to check.
    * @return True if data is valid, false otherwise.
    */
    bool isValidData(int year, int month) const;


};
#endif // STATISTICS_H_INCLUDED
