#include "WeatherLogType.h"
#include <iostream>

int main()
{

    WeatherLogType weatherLog;//create weather log object

    //Test GetInputFile Method()
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 1     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << ""<< std::endl;
    std::string fileName = weatherLog.GetInputFileName();
    std::cout << "CSV File Name: " << fileName << std::endl;

    //Test Load Record Method()
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 2     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << ""<< std::endl;
    int recordsLoaded = weatherLog.LoadRecords(fileName);
    std::cout << "Records Loaded: " << recordsLoaded << std::endl;

    //Check if record loaded more than 0
    if (recordsLoaded > 0)
    {
        int year = 2015; // Sample year
        int month = 3;   // sameple month

        //Call Average function to calculate speed,temp and solar radiation

        float avgSpeed = weatherLog.calculateAverage(0, year, month);

        float avgTemp = weatherLog.calculateAverage(1, year, month);

        float avgSolarRadiation = weatherLog.calculateAverage(2, year, month);

        //Print output
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 3     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "Average Wind Speed in " << month << "/" << year << ": " << avgSpeed << " km/h" << std::endl;
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 4     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "Average Temperature in " << month << "/" << year << ": " << avgTemp << " C" << std::endl;
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 5     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "Average Solar Radiation in " << month << "/" << year << ": " << avgSolarRadiation << " kWh/m2" << std::endl;

        //Call Std deviation function
        float stdDevSpeed = weatherLog.calculateStandardDeviation(0, year, month);
        float stdDevTemp = weatherLog.calculateStandardDeviation(1, year, month);


        //Print output
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 6     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << ""<< std::endl;
        std::cout << "Standard Deviation of Wind Speed: " << stdDevSpeed << std::endl;
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 7     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "Standard Deviation of Temperature: " << stdDevTemp << std::endl;
        std::cout << ""<< std::endl;

        //Call total radiation function
        float totalSolarRadiation = weatherLog.calculateTotalSolarRadiation(year, month);

        //print output
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 8     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << ""<< std::endl;
        std::cout << "Total Solar Radiation in " << month << "/" << year << ": " << totalSolarRadiation << " kWh/m2" << std::endl;

        //call display function to screen for average wind speed and sample std deviation
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 9     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << ""<< std::endl;
        weatherLog.printAverageAndStdDevToScreen(1, year, month);

        //call display funtion to screen for average temp and sample std deviation
        std::cout << ""<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << "     Test ID 10     "<< std::endl;
        std::cout << "-------------------"<< std::endl;
        std::cout << ""<< std::endl;
        weatherLog.printAverageAndStdDevToScreen(2, year, month);
    }

    return 0;
}
