#include "WeatherLogType.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>

// Add these definitions:
float WeatherLogType::accumulatedSpeed = 0.0;
float WeatherLogType::accumulatedTemp = 0.0;
float WeatherLogType::accumulatedSolar = 0.0;
int WeatherLogType::accumulatedCount = 0;
float WeatherLogType::accumulatedSquaredSpeedDiff = 0.0;
float WeatherLogType::accumulatedSquaredTempDiff = 0.0;
float WeatherLogType::averageSpeed = 0.0;
float WeatherLogType::averageTemp = 0.0;
Vector<WeatherLogType::WeatherData> WeatherLogType::currentData;

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

    Vector<std::string> fileNames; // Use your custom Vector class

    if (!inFile)
    {
        std::cout << "Error: Unable to open data_source.txt." << std::endl;
        return fileNames; // Return an empty Vector
    }

    std::string inputFileName;

    while (getline(inFile, inputFileName)) // Read each line
    {
        if (!inputFileName.empty())
        {
            fileNames.Insert("data/" + inputFileName, fileNames.GetSize()); // Insert file name into the Vector
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
    Vector<std::string> csvFiles = GetInputFileNames(); // Get all file names

    for (int i = 0; i < csvFiles.GetSize(); ++i) // Iterate through the Vector
    {
        std::string csvFile = csvFiles[i]; // Get the file name
        std::ifstream inFile(csvFile);

        if (!inFile)
        {
            std::cout << "Error opening file: " << csvFile << std::endl;
            continue; // Skip to the next file
        }

        std::cout << "Reading file: " << csvFile << std::endl; // Print file being read

        // Read the header
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

        // Loop through the header to find the columns
        while (getline(ssHeader, m_columnName, CSV_DELIMITER))
        {
            if (m_columnName == "WAST")
            {
                m_dateTimeColumnNum = m_colmunNum; //Store the date/time column number
            }
            else if (m_columnName == "S")
            {
                m_speedColumnNum = m_colmunNum;  // Store the Speed column number
            }
            else if (m_columnName == "T")
            {
                m_tempColumnNum = m_colmunNum;  // Store the Temperature column number
            }
            else if (m_columnName == "SR")
            {
                m_solarRadColumnNum = m_colmunNum;  // Store the Solar Radiation column number
            }
            m_colmunNum++;
        }

        std::string line;
        std::string tempStr, tempDateStr, tempTimeStr;
        int fileRecordCount = 0; // Counter for records in the current file

        // Loop through each line
        while (getline(inFile, line))
        {
            Vector<std::string> rowValues;
            std::stringstream ss(line);
            while (getline(ss, tempStr, CSV_DELIMITER))
            {
                rowValues.Insert(tempStr, rowValues.GetSize());
            }

            // Ensure rowValues has enough columns
            if (rowValues.GetSize() <= m_dateTimeColumnNum || rowValues.GetSize() <= m_speedColumnNum ||
                    rowValues.GetSize() <= m_tempColumnNum || rowValues.GetSize() <= m_solarRadColumnNum)
            {
                continue; // Skip this row
            }

            if (rowValues[m_speedColumnNum] == "N/A" || rowValues[m_tempColumnNum] == "N/A" || rowValues[m_solarRadColumnNum] == "N/A")
            {
                continue; // Skip this row
            }

            if (rowValues[m_speedColumnNum].empty() || rowValues[m_tempColumnNum].empty() || rowValues[m_solarRadColumnNum].empty())
            {
                continue; // Skip this row
            }

            // Parse the combined date and time from the WAST column
            std::string dateTimeStr = rowValues[m_dateTimeColumnNum];

            // Use stringstream to parse date and time
            std::stringstream ssDateTime(dateTimeStr);
            std::string dateStr, timeStr;

            // Extract date and time
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

            // Read Speed, Temperature, and Solar Radiation with error handling


            windSpeed = stof(rowValues[m_speedColumnNum]);
            temperature = stof(rowValues[m_tempColumnNum]);
            solarRadiation = stof(rowValues[m_solarRadColumnNum]);


            // Create Weather Record
            WeatherRecType myWeatherRecord;
            myWeatherRecord.SetSpeed(windSpeed);
            myWeatherRecord.SetTemperature(temperature);
            myWeatherRecord.SetSolarRadiation(solarRadiation);
            myWeatherRecord.SetDate(Date(day, month, year));
            myWeatherRecord.SetTime(Time(hour, minute, 0));

            if (!weatherValues.has(year))
            {
                weatherValues.add(year, Map<int, BinarySearchTree<int>>());
                weatherData.add(year, Map<int, Vector<WeatherData>>());
            }
            if (!weatherValues.get(year).has(month))
            {
                weatherValues.get(year).add(month, BinarySearchTree<int>());
                weatherData.get(year).add(month, Vector<WeatherData>());
            }
            weatherValues.get(year).get(month).Insert(weatherData.get(year).get(month).GetSize());
            weatherData.get(year).get(month).Insert({windSpeed, temperature, solarRadiation, Date(day, month, year), Time(hour, minute, 0)}, weatherData.get(year).get(month).GetSize());



            totalCount++;
            fileRecordCount++; // Increment record count for the current file
        }

        inFile.close();

        // Print success message for the current file
        std::cout << "Successfully loaded " << fileRecordCount << " records from " << csvFile << std::endl;
    }

    // Print summary message
    std::cout << "Total records loaded from all files: " << totalCount << std::endl;

    return totalCount;
}
void WeatherLogType::accumulateData(int& index)
{
    WeatherData data = currentData[index];
    accumulatedSpeed += data.speed;
    accumulatedTemp += data.temperature;
    accumulatedSolar += data.solarRadiation;
    accumulatedCount++;
    accumulatedSquaredSpeedDiff += (data.speed - averageSpeed) * (data.speed - averageSpeed);
    accumulatedSquaredTempDiff += (data.temperature - averageTemp) * (data.temperature - averageTemp);
}

float WeatherLogType::calculateAverage(int avgType, int year, int month) const
{
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) return 0.0f;
    accumulatedSpeed = accumulatedTemp = accumulatedSolar = accumulatedCount = 0;
    currentData = weatherData.get(year).get(month);
    weatherValues.get(year).get(month).InorderTraversal(accumulateData);
    if (accumulatedCount == 0) return 0.0f;
    if (avgType == 0) return (accumulatedSpeed / accumulatedCount) * 3.6f;
    else if (avgType == 1) return accumulatedTemp / accumulatedCount;
    else return accumulatedSolar / accumulatedCount;
}

float WeatherLogType::calculateStandardDeviation(int stdDeviationType, int year, int month) const
{
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) return 0.0f;
    averageSpeed = calculateAverage(0, year, month);
    averageTemp = calculateAverage(1, year, month);
    accumulatedSquaredSpeedDiff = accumulatedSquaredTempDiff = accumulatedCount = 0;
    currentData = weatherData.get(year).get(month);
    weatherValues.get(year).get(month).InorderTraversal(accumulateData);
    if (accumulatedCount <= 1) return 0.0f;
    if (stdDeviationType == 0) return sqrt(accumulatedSquaredSpeedDiff / (accumulatedCount - 1));
    else return sqrt(accumulatedSquaredTempDiff / (accumulatedCount - 1));
}

float WeatherLogType::calculateTotalSolarRadiation(int year, int month) const
{
    if (!weatherData.has(year) || !weatherData.get(year).has(month)) return 0.0f;
    accumulatedSolar = accumulatedCount = 0;
    currentData = weatherData.get(year).get(month);
    weatherValues.get(year).get(month).InorderTraversal(accumulateData);
    return accumulatedSolar;
}


void WeatherLogType::printAverageAndStdDevToScreen(int choice, int year, int month) const
{
    const std::string monthName[] = {"January", "February", "March", "April", "May", "June",
                                     "July", "August", "September", "October", "November", "December"
                                    };

    if (choice == 1)
    {
        float avgSpeed = calculateAverage(0, year, month);
        float stdDevSpeed = calculateStandardDeviation(0, year, month);

        if (avgSpeed > 0)
        {
            // Write the month name and print average speed and std deviation to 2 decimal place
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
            float avgTemp = calculateAverage(1, year, month);
            float stdDevTemp = calculateStandardDeviation(1, year, month);

            if (avgTemp > 0)
            {
                // Write the month name and print average temp to 2 decimal place
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
            float totalSolarRadiation = calculateTotalSolarRadiation(year,month);


            if (totalSolarRadiation > 0)
            {
                // Write the month name and print total radiation to 2 decimal place
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
    //Declare monthName array to convert month number to name
    const std::string monthName[] = {"January", "February", "March", "April", "May", "June",
                                     "July", "August", "September", "October", "November", "December"
                                    };

    std::ofstream outFile("WindTempSolar.csv");

    if (choice == 4)
    {
        outFile << year << std::endl;

        bool hasDataForYear = false;

        for (int month = 1; month <= 12; ++month)
        {
            //Initialise and call function
            float avgSpeed = calculateAverage(0, year, month);
            float stdDevSpeed = calculateStandardDeviation(0, year, month);
            float avgTemp = calculateAverage(1, year, month);
            float stdDevTemp = calculateStandardDeviation(1, year, month);
            float totalSolarRadiation = calculateTotalSolarRadiation(year, month);


            //Check if average data is more than 0 than declare as year have data
            if (avgSpeed > 0 || avgTemp > 0 || totalSolarRadiation > 0)
            {
                hasDataForYear = true;

                outFile << monthName[month - 1] << ","; // Write the month name

                if (avgSpeed > 0)
                {
                    //Round to 2 decimal place
                    outFile << std::fixed << std::setprecision(2) << avgSpeed << "(" << stdDevSpeed << ")";
                }
                outFile << ",";

                if (avgTemp > 0)
                {
                    //Round to 2 decimal place
                    outFile << std::fixed << std::setprecision(2) << avgTemp << "(" << stdDevTemp << ")";
                }
                outFile << ",";

                if (totalSolarRadiation > 0)
                {
                    //Round to 2 decimal place
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


