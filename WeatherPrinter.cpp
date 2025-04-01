#include "WeatherPrinter.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Initializes stats with weather data from the WeatherLog
WeatherPrinter::WeatherPrinter(const WeatherLogType& weatherLog): stats(weatherLog.GetWeatherData()) {}

WeatherPrinter::~WeatherPrinter() {}

void WeatherPrinter::printToScreen(const WeatherLogType& weatherLog, int choice, int year, int month) const
{
    const std::string monthName[] = {"January", "February", "March", "April", "May", "June",
                                     "July", "August", "September", "October", "November", "December"};

    if (choice == 1)
    {
        //Call functions from statistics class
        float avgSpeed = stats.calculateAverage(0, year, month);
        float stdDevSpeed = stats.calculateStandardDeviation(0, year, month);

        if (avgSpeed > 0)
        {
            std::cout << monthName[month - 1] << " " << year << ":" << std::endl;
            std::cout << "Average speed: " << std::fixed << std::setprecision(2) << avgSpeed << " km/h" << std::endl;
            std::cout << "Sample stdev: " << std::fixed << std::setprecision(2) << stdDevSpeed << std::endl;
        }
        else
        {
            std::cout << monthName[month - 1] << " " << year << ": No Data" << std::endl;
        }
    }
    else if (choice == 2)
    {
        std::cout << year << std::endl;
        for (int mth = 1; mth <= 12; ++mth)
        {
            //Call functions from statistics class
            float avgTemp = stats.calculateAverage(1, year, mth);
            float stdDevTemp = stats.calculateStandardDeviation(1, year, mth);

            if (avgTemp > 0)
            {
                std::cout << monthName[mth - 1] << ": average: " << std::fixed << std::setprecision(2)
                          << avgTemp << " degrees C, stdev: " << std::fixed << std::setprecision(2)
                          << stdDevTemp << std::endl;
            }
            else
            {
                std::cout << monthName[mth - 1] << ": No Data" << std::endl;
            }
        }
    }
    else if (choice == 3)
    {
        std::cout << "Sample Pearson Correlation Coefficient for " << monthName[month - 1] << std::endl;

        //Call functions from statistics class
        float sT,sR,tR;

        sT= stats.calculateSPCC(0, year, month);  // Speed vs Temperature

        sR= stats.calculateSPCC(1, year, month);  // Speed vs Radiation

        tR= stats.calculateSPCC(2, year, month);  // Temperature vs Radiation

        std::cout << "S_T: " << std::fixed << std::setprecision(2) << sT << std::endl;
        std::cout << "S_R: " << std::fixed << std::setprecision(2) << sR << std::endl;
        std::cout << "T_R: " << std::fixed << std::setprecision(2) << tR << std::endl;
    }
}

void WeatherPrinter::printToFile(const WeatherLogType& weatherLog, int choice, int year, int month) const
{
    const std::string monthName[] = {"January", "February", "March", "April", "May", "June",
                                     "July", "August", "September", "October", "November", "December"};

    std::ofstream outFile("WindTempSolar.csv");

    if (choice == 4)
    {
        outFile << year << std::endl;

        bool hasDataForYear = false;

        for (int mth = 1; mth <= 12; ++mth)
        {
            // Speed statistics
            float avgSpeed = stats.calculateAverage(0, year, mth);
            float stdDevSpeed = stats.calculateStandardDeviation(0, year, mth);
            float madSpeed = stats.calculateMAD(0, year, mth);

            // Temperature statistics
            float avgTemp = stats.calculateAverage(1, year, mth);
            float stdDevTemp = stats.calculateStandardDeviation(1, year, mth);
            float madTemp = stats.calculateMAD(1, year, mth);

            // Solar radiation
            float totalSolarRadiation = stats.calculateTotalSolarRadiation(year, mth);

            if (avgSpeed > 0 || avgTemp > 0 || totalSolarRadiation > 0)
            {
                hasDataForYear = true;

                outFile << monthName[mth - 1] << ",";

                // Speed output
                if (avgSpeed > 0)
                {
                    outFile << std::fixed << std::setprecision(2) << avgSpeed << "("
                            << std::fixed << std::setprecision(2) << stdDevSpeed << ","
                            << std::fixed << std::setprecision(2) << madSpeed << ")";
                }
                outFile << ",";

                // Temperature output
                if (avgTemp > 0)
                {
                    outFile << std::fixed << std::setprecision(2) << avgTemp << "("
                            << std::fixed << std::setprecision(2) << stdDevTemp << ","
                            << std::fixed << std::setprecision(2) << madTemp << ")";
                }
                outFile << ",";

                // Solar radiation output
                if (totalSolarRadiation > 0)
                {
                    outFile << std::fixed << std::setprecision(2) << totalSolarRadiation;
                }

                outFile << std::endl;
            }
        }

        if (!hasDataForYear)
        {
            outFile << "No Data" << std::endl;
        }
    }

    outFile.close();
}
