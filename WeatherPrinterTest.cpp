#include <string>
#include <iostream>
#include <fstream>
#include "WeatherLogType.h"
#include "WeatherPrinter.h"


int main() {


    // Create a WeatherLogType object
    WeatherLogType weatherLog;

    //1. Input/Load
    std::string csvFileName;
    int recordsLoaded = weatherLog.LoadRecords(csvFileName);
     if (recordsLoaded < 0)
    {
        std::cout << "Error loading records. Exiting program." << std::endl;
        return 1;
    }

    // Create the WeatherPrinter object
    WeatherPrinter weatherPrinter(weatherLog);

    // Test printToScreen function (choice = 1, year = 2015, month = 1)
    std::cout << "Testing printToScreen with choice 1 (Average Speed and Standard Deviation):" << std::endl;
    weatherPrinter.printToScreen(weatherLog, 1, 2015, 1);
    std::cout << std::endl;

    // Test printToScreen function (choice = 2, year = 2015)
    std::cout << "Testing printToScreen with choice 2 (Average Temperature and Standard Deviation for All Months):" << std::endl;
    weatherPrinter.printToScreen(weatherLog, 2, 2015, 0);  // All months
    std::cout << std::endl;

    // Test printToScreen function (choice = 3, year = 2015, month = 1)
    std::cout << "Testing printToScreen with choice 3 (SPCC for Speed, Temperature, and Radiation):" << std::endl;
    weatherPrinter.printToScreen(weatherLog, 3, 2015, 3);
    std::cout << std::endl;

    // Test printToFile function (choice = 4, year = 2015)
    std::cout << "Testing printToFile with choice 4 (Export data to file):" << std::endl;
    weatherPrinter.printToFile(weatherLog, 4, 2015, 0);  // All months


    return 0;
}
