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

    // Add this public getter method
    const Map<int, Map<int, Vector<WeatherRecType>>>& GetWeatherData() const;



private:


    typedef BinarySearchTree<int> ValueTree;
    typedef Map<int, ValueTree> MonthValues;
    typedef Map<int, Map<int, Vector<WeatherRecType>>> MonthData;
    typedef Map<int, MonthValues> YearValues;
    YearValues weatherValues;
    MonthData weatherData;





};

#endif // WEATHERLOGTYPE_H_INCLUDED
