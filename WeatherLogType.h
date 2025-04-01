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
     * @brief Retrieves the stored weather data.
     *
     * This function returns the weather data organized by year, month, and a list of weather records.
     *
     * @return A reference to the weather data map.
     */
    const Map<int, Map<int, Vector<WeatherRecType>>>& GetWeatherData() const;



private:


    typedef BinarySearchTree<int> ValueTree; /// A binary search tree storing weather values.
    typedef Map<int, ValueTree> MonthValues; /// A map storing weather values for each month.
    typedef Map<int, Map<int, Vector<WeatherRecType>>> MonthData;  /// A nested map storing weather records, organized by year and month.
    typedef Map<int, MonthValues> YearValues;/// A map that stores values for each year, with months as keys.
    YearValues weatherValues; /// Stores the weather values, organized by year and month.
    MonthData weatherData; /// Stores detailed weather data, organized by year and month.





};

#endif // WEATHERLOGTYPE_H_INCLUDED
