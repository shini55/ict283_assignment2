#ifndef WEATHERLOGTYPE_H_INCLUDED
#define WEATHERLOGTYPE_H_INCLUDED
#include "Vector.h"
#include "WeatherRecType.h"
#include <string>
#include "Map.h"
#include "BinarySearchTree.h"

/**
 * @class WeatherLogType
 * @brief A class to manage weather records, perform calculations, and output data.
 */


class WeatherLogType
{
public:

    /**
     * @brief Default constructor for WeatherLogType.
     */
    WeatherLogType();

    /**
     * @brief Destructor for WeatherLogType.
     */
    ~WeatherLogType();

    /**
     * @brief Gets the name of the input file.
     * @return A string containing the input file name.
     */
    Vector<std::string> GetInputFileNames();

    /**
    * @brief Loads weather records from a specified file.
    * @param filename The name of the file containing weather data.
    * @return The number of records successfully loaded.
    */
    int LoadRecords(const std::string &filename);

    /**
    * @brief Calculates the average of a specific weather parameter for a given month and year.
    * @param avgType The type of weather parameter (e.g., wind speed, temperature, or solar radiation).
    * @param month The month for which the average is calculated.
    * @param year The year for which the average is calculated.
    * @return The calculated average as a float.
    */
    float calculateAverage(int avgType,int month, int year) const;

    /**
    * @brief Calculates the standard deviation of a specific weather parameter for a given month and year.
    * @param stdDeviationType The type of weather parameter (e.g., wind speed, temperature, or solar radiation).
    * @param month The month for which the standard deviation is calculated.
    * @param year The year for which the standard deviation is calculated.
    * @return The calculated standard deviation as a float.
    */
    float calculateStandardDeviation(int stdDeviationType,int month, int year) const;

    /**
     * @brief Calculates the total solar radiation for a given month and year.
     * @param year The year for which the total solar radiation is calculated.
     * @param month The month for which the total solar radiation is calculated.
     * @return The total solar radiation as a float.
     */
    float calculateTotalSolarRadiation(int year, int month) const;

    /**
    * @brief Prints the calculated average and standard deviation to the screen.
    * @param choice The type of weather parameter to print.
    * @param month The month for which data is printed.
    * @param year The year for which data is printed.
    */
    void printAverageAndStdDevToScreen(int choice, int month,int year) const;

    /**
    * @brief Prints the calculated average and total solar radiation to a file.
    * @param choice The type of weather parameter to print.
    * @param month The month for which data is printed.
    * @param year The year for which data is printed.
    */
    void printAverageAndTotalToFile(int choice, int month,int year) const;

    /**
    * @brief Prints all loaded weather data to a specified output file.
    * @param outputFilename The name of the output file.
    */
    void printLoadedDataToFile(const std::string &outputFilename) const;
    static Vector<float> staticTraversalValues; // Static vector



private:

    struct WeatherData
{
    float speed;
    float temperature;
    float solarRadiation;
    Date date;
    Time time;
};

    typedef BinarySearchTree<int> ValueTree;
    typedef Map<int, ValueTree> MonthValues;
    typedef Map<int, Map<int, Vector<WeatherData>>> MonthData;
    typedef Map<int, MonthValues> YearValues;
    YearValues weatherValues;
    MonthData weatherData;

    static void accumulateData(int& index);
    static float accumulatedSpeed;
    static float accumulatedTemp;
    static float accumulatedSolar;
    static int accumulatedCount;
    static float accumulatedSquaredSpeedDiff;
    static float accumulatedSquaredTempDiff;
    static float averageSpeed;
    static float averageTemp;
    static int currentIndex;
    static Vector<WeatherData> currentData;

};

#endif // WEATHERLOGTYPE_H_INCLUDED
