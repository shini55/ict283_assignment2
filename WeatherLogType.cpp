#include "WeatherLogType.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>
#include "Statistics.h" // Include statistics.h

WeatherLogType::WeatherLogType()
{
}

WeatherLogType::~WeatherLogType()
{
}

Vector<std::string> WeatherLogType::GetInputFileNames()
{
    std::string txtFile = "data/data_source.txt";
    std::ifstream inFile(txtFile);

    Vector<std::string> fileNames;

    if (!inFile)
    {
        std::cout << "Error: Unable to open data_source.txt." << std::endl;
        return fileNames;
    }

    std::string inputFileName;

    while (getline(inFile, inputFileName))
    {
        if (!inputFileName.empty())
        {
            fileNames.Insert("data/" + inputFileName, fileNames.GetSize());
        }
    }
    inFile.close();

    if (fileNames.GetSize() == 0)
    {
        std::cout << "No filenames found in " << txtFile << std::endl;
    }

    return fileNames;
}

int WeatherLogType::LoadRecords(const std::string &filename)
{
    int totalCount = 0;
    Vector<std::string> csvFiles = GetInputFileNames();

    for (int i = 0; i < csvFiles.GetSize(); ++i)
    {
        std::string csvFile = csvFiles[i];
        std::ifstream inFile(csvFile);

        if (!inFile)
        {
            std::cout << "Error opening file: " << csvFile << std::endl;
            continue;
        }

        std::cout << "Reading file: " << csvFile << std::endl;

        std::string header;
        getline(inFile, header);
        char CSV_DELIMITER = ',';

        std::stringstream ssHeader(header);
        std::string m_columnName;
        int m_speedColumnNum = -1;
        int m_tempColumnNum = -1;
        int m_solarRadColumnNum = -1;
        int m_dateTimeColumnNum = -1;
        int m_colmunNum = 0;

        while (getline(ssHeader, m_columnName, CSV_DELIMITER))
        {
            if (m_columnName == "WAST")
            {
                m_dateTimeColumnNum = m_colmunNum;
            }
            else if (m_columnName == "S")
            {
                m_speedColumnNum = m_colmunNum;
            }
            else if (m_columnName == "T")
            {
                m_tempColumnNum = m_colmunNum;
            }
            else if (m_columnName == "SR")
            {
                m_solarRadColumnNum = m_colmunNum;
            }
            m_colmunNum++;
        }

        std::string line;
        std::string tempStr, tempDateStr, tempTimeStr;
        int fileRecordCount = 0;

        while (getline(inFile, line))
        {
            Vector<std::string> rowValues;
            std::stringstream ss(line);
            while (getline(ss, tempStr, CSV_DELIMITER))
            {
                rowValues.Insert(tempStr, rowValues.GetSize());
            }

            if (rowValues.GetSize() <= m_dateTimeColumnNum || rowValues.GetSize() <= m_speedColumnNum ||
                rowValues.GetSize() <= m_tempColumnNum || rowValues.GetSize() <= m_solarRadColumnNum)
            {
                continue;
            }

            if (rowValues[m_speedColumnNum] == "N/A" || rowValues[m_tempColumnNum] == "N/A" || rowValues[m_solarRadColumnNum] == "N/A")
            {
                continue;
            }

            if (rowValues[m_speedColumnNum].empty() || rowValues[m_tempColumnNum].empty() || rowValues[m_solarRadColumnNum].empty())
            {
                continue;
            }

            std::string dateTimeStr = rowValues[m_dateTimeColumnNum];

            std::stringstream ssDateTime(dateTimeStr);
            std::string dateStr, timeStr;

            ssDateTime >> dateStr >> timeStr;

            std::stringstream ssDate(dateStr);
            int day, month, year;
            char DATE_DELIMITER = '/';
            ssDate >> day >> DATE_DELIMITER >> month >> DATE_DELIMITER >> year;

            std::stringstream ssTime(timeStr);
            int hour, minute;
            char TIME_DELIMITER = ':';
            ssTime >> hour >> TIME_DELIMITER >> minute;

            float windSpeed = 0.0, temperature = 0.0, solarRadiation = 0.0;

            windSpeed = stof(rowValues[m_speedColumnNum]);
            temperature = stof(rowValues[m_tempColumnNum]);
            solarRadiation = stof(rowValues[m_solarRadColumnNum]);

            WeatherRecType myWeatherRecord;
            myWeatherRecord.SetSpeed(windSpeed);
            myWeatherRecord.SetTemperature(temperature);
            myWeatherRecord.SetSolarRadiation(solarRadiation);
            myWeatherRecord.SetDate(Date(day, month, year));
            myWeatherRecord.SetTime(Time(hour, minute, 0));

            if (!weatherValues.has(year))
            {
                weatherValues.add(year, Map<int, BinarySearchTree<int>>());
                weatherData.add(year, Map<int, Vector<WeatherRecType>>());
            }
            if (!weatherValues.get(year).has(month))
            {
                weatherValues.get(year).add(month, BinarySearchTree<int>());
                weatherData.get(year).add(month, Vector<WeatherRecType>());
            }
             weatherValues.get(year).get(month).Insert(weatherData.get(year).get(month).GetSize());
             weatherData.get(year).get(month).Insert(myWeatherRecord, weatherData.get(year).get(month).GetSize());

            totalCount++;
            fileRecordCount++;
        }

        inFile.close();
        std::cout << "Successfully loaded " << fileRecordCount << " records from " << csvFile << std::endl;
    }

    std::cout << "Total records loaded from all files: " << totalCount << std::endl;
    return totalCount;
}

void WeatherLogType::printAverageAndStdDevToScreen(int choice, int year, int month) const
{
    const std::string monthName[] = {"January", "February", "March", "April", "May", "June",
                                      "July", "August", "September", "October", "November", "December"};

    if (choice == 1)
    {
        float avgSpeed = stats.calculateAverage(0, year, month, weatherData, weatherValues);
        float stdDevSpeed = stats.calculateStandardDeviation(0, year, month, weatherData, weatherValues);

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
        for (int month = 1; month <= 12; ++month)
        {
            float avgTemp = stats.calculateAverage(1, year, month, weatherData, weatherValues);
            float stdDevTemp = stats.calculateStandardDeviation(1, year, month, weatherData, weatherValues);

            if (avgTemp > 0)
            {
                std::cout << monthName[month - 1] << ": average: " << std::fixed << std::setprecision(2) << avgTemp << " degrees C, stdev: " << std::fixed << std::setprecision(2) << stdDevTemp << std::endl;
            }
            else
            {
                std::cout << monthName[month - 1] << ": No Data" << std::endl;
            }
        }
    }
    else if (choice == 3)
    {
        std::cout << "";
        for (int month = 1; month <= 12; ++month)
        {
            float totalSolarRadiation = stats.calculateTotalSolarRadiation(year, month, weatherData, weatherValues);

            if (totalSolarRadiation > 0)
            {
                std::cout << monthName[month - 1] << ":" << std::fixed << std::setprecision(2) << totalSolarRadiation << " kWh/m2" << std::endl;
            }
            else
            {
                std::cout << monthName[month - 1] << ": No Data" << std::endl;
            }
        }
    }
}

void WeatherLogType::printAverageAndTotalToFile(int choice, int year, int month) const
{
    const std::string monthName[] = {"January", "February", "March", "April", "May", "June",
                                      "July", "August", "September", "October", "November", "December"};

    std::ofstream outFile("WindTempSolar.csv");

    if (choice == 4)
    {
        outFile << year << std::endl;

        bool hasDataForYear = false;

        for (int month = 1; month <= 12; ++month)
        {
            float avgSpeed = stats.calculateAverage(0, year, month, weatherData, weatherValues);
            float stdDevSpeed = stats.calculateStandardDeviation(0, year, month, weatherData, weatherValues);
            float avgTemp = stats.calculateAverage(1, year, month, weatherData, weatherValues);
            float stdDevTemp = stats.calculateStandardDeviation(1, year, month, weatherData, weatherValues);
            float totalSolarRadiation = stats.calculateTotalSolarRadiation(year, month, weatherData, weatherValues);

            if (avgSpeed > 0 || avgTemp > 0 || totalSolarRadiation > 0)
            {
                hasDataForYear = true;

                outFile << monthName[month - 1] << ",";

                if (avgSpeed > 0)
                {
                    outFile << std::fixed << std::setprecision(2) << avgSpeed << "(" << stdDevSpeed << ")";
                }
                outFile << ",";

                if (avgTemp > 0)
                {
                    outFile << std::fixed << std::setprecision(2) << avgTemp << "(" << stdDevTemp << ")";
                }
                outFile << ",";

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
