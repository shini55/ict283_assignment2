#include "WeatherLogType.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>
#include "Statistics.h"


const Map<int, Map<int, Vector<WeatherRecType>>>& WeatherLogType::GetWeatherData() const
{
    return weatherData;// Returns the stored weather data to use in statistics class
}
WeatherLogType::WeatherLogType()
{
}

WeatherLogType::~WeatherLogType()
{
}

Vector<std::string> WeatherLogType::GetInputFileNames()
{
    std::string txtFile = "data/data_source.txt";// File containing names of data files
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
            fileNames.Insert("data/" + inputFileName, fileNames.GetSize());// Store full file path
        }
    }
    inFile.close();

    if (fileNames.GetSize() == 0)
    {
        std::cout << "No filenames found in " << txtFile << std::endl;
    }

    return fileNames;// Return list of filenames
}

int WeatherLogType::LoadRecords(const std::string &filename)
{
    int totalCount = 0;
    Vector<std::string> csvFiles = GetInputFileNames();// Get list of CSV files

    for (int i = 0; i < csvFiles.GetSize(); ++i)
    {
        std::string csvFile = csvFiles[i];
        std::ifstream inFile(csvFile);

        if (!inFile)
        {
            std::cout << "Error opening file: " << csvFile << std::endl;
            continue;// Skip this file if it can't be opened
        }

        std::cout << "Reading file: " << csvFile << std::endl;

        std::string header;
        getline(inFile, header);// Read the header line
        char CSV_DELIMITER = ',';

        std::stringstream ssHeader(header);
        std::string m_columnName;
        int m_speedColumnNum = -1;
        int m_tempColumnNum = -1;
        int m_solarRadColumnNum = -1;
        int m_dateTimeColumnNum = -1;
        int m_colmunNum = 0;

        // Identify column positions in the file
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
            Vector<std::string> rowValues;// Store column values from the current CSV row
            std::stringstream ss(line);
            while (getline(ss, tempStr, CSV_DELIMITER))
            {
                rowValues.Insert(tempStr, rowValues.GetSize());// Insert each value into rowValues
            }

             // Skip rows with missing or "N/A" values
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

            std::string dateTimeStr = rowValues[m_dateTimeColumnNum];// Extract date and time from the row


             // Extract date and time
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


            // Convert string values to float
            windSpeed = stof(rowValues[m_speedColumnNum]);
            temperature = stof(rowValues[m_tempColumnNum]);
            solarRadiation = stof(rowValues[m_solarRadColumnNum]);

             // Create a weather record and set weather datas
            WeatherRecType myWeatherRecord;
            myWeatherRecord.SetSpeed(windSpeed);
            myWeatherRecord.SetTemperature(temperature);
            myWeatherRecord.SetSolarRadiation(solarRadiation);
            myWeatherRecord.SetDate(Date(day, month, year));
            myWeatherRecord.SetTime(Time(hour, minute, 0));

            // Checks if year exists in the map
            if (!weatherValues.has(year))
            {
                //Creates a new entry for the year with an empty map of months
                weatherValues.add(year, Map<int, BinarySearchTree<int>>());// Store sorted indices for each month
                weatherData.add(year, Map<int, Vector<WeatherRecType>>()); // Store weather records for each month
            }

            // Checks if month exists in that year's map
            if (!weatherValues.get(year).has(month))
            {
                //Creates a new entry for the month with a BST for indices and a vector for records
                weatherValues.get(year).add(month, BinarySearchTree<int>());

                weatherData.get(year).add(month, Vector<WeatherRecType>());
            }

            // Insert the position of the new record into the Binary Search Tree for the specific year and month
            weatherValues.get(year).get(month).Insert(weatherData.get(year).get(month).GetSize());

            // Insert the actual weather record into the vector for the specific year and month
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

