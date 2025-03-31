#ifndef WEATHERLOGTYPE_H_INCLUDED
#define WEATHERLOGTYPE_H_INCLUDED
#include "Vector.h"
#include "WeatherRecType.h"
#include <string>
#include "Map.h"
#include "BinarySearchTree.h"
#include "Statistics.h"
#include "WeatherRecType.h" // Include WeatherRecType.h

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




private:


    typedef BinarySearchTree<int> ValueTree;
    typedef Map<int, ValueTree> MonthValues;
    typedef Map<int, Map<int, Vector<WeatherRecType>>> MonthData;
    typedef Map<int, MonthValues> YearValues;
    YearValues weatherValues;
    MonthData weatherData;


    Statistics stats; // Add Statistics object


};

#endif // WEATHERLOGTYPE_H_INCLUDED
