// statistics.cpp
#include "Statistics.h"
#include <cmath>


// Initializes the Statistics object with weather data and populates valid years and months.
Statistics::Statistics(const Map<int, Map<int, Vector<WeatherRecType>>>& weatherData):weatherData(weatherData)
{
    populateValidData();// populate validYears and validMonths based on available data to BST
}

void Statistics::populateValidData()
{

    // Loop through possible years from 1999 to 2100
    for (int year = 1999; year <= 2100; ++year)
    {
        // Check if data exists for this year
        if (weatherData.has(year))
        {
            validYears.Insert(year);// Add year to the list of valid years binary search tree

          
            for (int month = 1; month <= 12; ++month)
            {
                if (weatherData.get(year).has(month))// Add month to the list of valid months binary search tree
                {
                    validMonths.Insert(month);
                }
            }
        }
    }
}

bool Statistics::isValidData(int year, int month) const
{
    // Check if the given year exists in the list of valid years
    // or if the given month exists in the list of valid months
    if (!validYears.Search(year) || !validMonths.Search(month))
    {
        return false;// If either is missing, the data is invalid
    }

    
    return weatherData.has(year) && weatherData.get(year).has(month);
}


float Statistics::calculateAverage(int avgType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0;
    }

    const Vector<WeatherRecType>& monthRecords = weatherData.get(year).get(month);

    float totalSpeed = 0.0, totalTemperature = 0.0, totalSolarRadiation = 0.0;
    int totalNumOfData = monthRecords.GetSize();
    const float SPEED_CONVERSION_kmH = 3.6; // Converts m/s to km/h

    if (totalNumOfData == 0)
    {
        return 0.0;
    }

    for (int i = 0; i < totalNumOfData; ++i)
    {
        //calculate all the speed,temp and solar radiation
        totalSpeed = totalSpeed + monthRecords[i].GetSpeed();
        totalTemperature = totalTemperature + monthRecords[i].GetTemperature();
        totalSolarRadiation = totalSolarRadiation + monthRecords[i].GetSolarRadiation();
    }

    switch (avgType)
    {
    case 0:
        return (totalSpeed / totalNumOfData) * SPEED_CONVERSION_kmH; // Use the stored variable
    case 1:
        return totalTemperature / totalNumOfData;
    case 2:
        return totalSolarRadiation / totalNumOfData;
    default:
        return 0.0;
    }
}

float Statistics::calculateStandardDeviation(int stdDeviationType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0;
    }

    float sumSpeed = 0.0;
    float sumTemperature = 0.0;
    int totalNumOfData = 0;

    float avgSpeed = calculateAverage(0, year, month);
    float avgTemperature = calculateAverage(1, year, month);

    const Vector<WeatherRecType>& monthRecords = weatherData.get(year).get(month);
    for (int i = 0; i < monthRecords.GetSize(); i++)
    {
        //calculated the std deviation by first minusing the mean
        float speedDiff = monthRecords[i].GetSpeed() - avgSpeed;
        sumSpeed = sumSpeed + (speedDiff * speedDiff);

        float tempDiff = monthRecords[i].GetTemperature() - avgTemperature;
        sumTemperature = sumTemperature + (tempDiff * tempDiff);

        totalNumOfData++;
    }

    if (totalNumOfData <= 1)
    {
        return 0.0;
    }

    switch (stdDeviationType)
    {
    case 0:
        return sqrt(sumSpeed / (totalNumOfData - 1));
    case 1:
        return sqrt(sumTemperature / (totalNumOfData - 1));
    default:
        return 0.0;
    }
}

float Statistics::calculateTotalSolarRadiation(int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0f;
    }

    float totalSolarRadiationkWh = 0.0f;
    const Vector<WeatherRecType>& monthRecords = weatherData.get(year).get(month);

    // Conversion factors
    const float HOURS_PER_RECORD = 1.0f / 6.0f; // Each record represents 10 minutes (1/6 of an hour)
    const float WATTS_TO_KILOWATTS = 1.0f / 1000.0f; // Convert from watts to kilowatts
    const float MINIMUM_RADIATION = 100.0f; // Minimum radiation value

    for (int i = 0; i < monthRecords.GetSize(); ++i)
    {
        float solarRadiationWm2 = monthRecords[i].GetSolarRadiation();
        if (solarRadiationWm2 >= MINIMUM_RADIATION)
        {
            //convert solar raditon to kWhm2
            float solarRadiationkWhm2 = (solarRadiationWm2 * HOURS_PER_RECORD) * WATTS_TO_KILOWATTS;
            totalSolarRadiationkWh = totalSolarRadiationkWh + solarRadiationkWhm2;
        }
    }

    return totalSolarRadiationkWh;
}


float Statistics::calculateMeanForSPCCandMAD(const Vector<float>& values) const
{
    if (values.GetSize() == 0)  // Check if there are no values to avoid division by zero
    {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < values.GetSize(); ++i)  // Loop through each value in the vector
    {
        sum = sum + values[i];  // Add the current value to the sum
    }


    return sum / values.GetSize();
}


float Statistics::calculateStandardDeviationForSPCC(const Vector<float>& values, float mean) const
{
    if (values.GetSize() == 0)  // Check if there are no values to avoid division by zero
    {
        return 0.0f;
    }

    float totalDifferenceSquared = 0.0f;
    for (int i = 0; i < values.GetSize(); ++i)  // Loop through each value
    {
        // Calculate the difference from the mean, square it, and add to the total
        totalDifferenceSquared += (values[i] - mean) * (values[i] - mean);
    }


    return sqrt(totalDifferenceSquared / (values.GetSize() - 1));
}

float Statistics::calculateSPCC(int combinationType, int year, int month) const
{

    //Validate if year and month exist before calculating
    if (!isValidData(year, month))
    {
        return 0.0f;
    }


    //create vector to store the speed,temp and solar radition
    Vector<float> allSpeeds;
    Vector<float> allTemps;
    Vector<float> allSolar;
    const Vector<WeatherRecType>& records = weatherData.get(year).get(month);


    for (int i = 0; i < records.GetSize(); i = i + 1)
    {
        //Insert all the data to the vector based on the month and year
        allSpeeds.Insert(records[i].GetSpeed(), allSpeeds.GetSize());
        allTemps.Insert(records[i].GetTemperature(), allTemps.GetSize());
        allSolar.Insert(records[i].GetSolarRadiation(), allSolar.GetSize());
    }


    //Validate and male sure that have 2 data sets to calculate spcc
    if (allSpeeds.GetSize() != allTemps.GetSize() ||
            allSpeeds.GetSize() != allSolar.GetSize())
    {
        return 0.0f;
    }
    if (allSpeeds.GetSize() < 2)
    {
        return 0.0f;
    }

    //calculate mean
    float avgSpeed = calculateMeanForSPCCandMAD(allSpeeds);
    float avgTemp = calculateMeanForSPCCandMAD(allTemps);
    float avgSolar = calculateMeanForSPCCandMAD(allSolar);

    //calculate std deviation
    float speedDeviation = calculateStandardDeviationForSPCC(allSpeeds, avgSpeed);
    float tempDeviation = calculateStandardDeviationForSPCC(allTemps, avgTemp);
    float solarDeviation = calculateStandardDeviationForSPCC(allSolar, avgSolar);


    float spcc = 0.0f;
    for (int i = 0; i < allSpeeds.GetSize(); i = i + 1)
    {
        //Taking all the speed valuse and minus the mean
        float speedDiff = allSpeeds[i] - avgSpeed;
        float tempDiff = allTemps[i] - avgTemp;
        float solarDiff = allSolar[i] - avgSolar;

        switch (combinationType)
        {
        case 0:
            spcc = spcc + (speedDiff * tempDiff);
            break;  // Speed & Temp
        case 1:
            spcc = spcc + (speedDiff * solarDiff);
            break;  // Speed & Solar
        case 2:
            spcc = spcc + (tempDiff * solarDiff);
            break;   // Temp & Solar
        default:
            return 0.0f;
        }
    }

    //Calculating the sPCC
    switch (combinationType)
    {
    case 0:
        if (speedDeviation == 0.0f || tempDeviation == 0.0f)
        {
            return 0.0f;
        }
        else
        {
            return spcc / ((allSpeeds.GetSize() - 1) * speedDeviation * tempDeviation);
        }

    case 1:
        if (speedDeviation == 0.0f || solarDeviation == 0.0f)
        {
            return 0.0f;
        }
        else
        {
            return spcc / ((allSpeeds.GetSize() - 1) * speedDeviation * solarDeviation);
        }

    case 2:
        if (tempDeviation == 0.0f || solarDeviation == 0.0f)
        {
            return 0.0f;
        }
        else
        {
            return spcc / ((allSpeeds.GetSize() - 1) * tempDeviation * solarDeviation);
        }

    default:
        return 0.0f;
    }
}

float Statistics::calculateMAD(int madType, int year, int month) const
{
    if (!isValidData(year, month))
    {
        return 0.0f;
    }

    Vector<float> values;
    const Vector<WeatherRecType>& records = weatherData.get(year).get(month);

    float sum = 0.0f;
    for (int i = 0; i < records.GetSize(); ++i)
    {
        float value = 0.0f;
        switch (madType)
        {
        case 0:  // Speed data
            value = records[i].GetSpeed();
            break;
        case 1:  // Temperature data
            value = records[i].GetTemperature();
            break;
        default:
            return 0.0f;
        }
        values.Insert(value, values.GetSize());
        sum = sum + value;  // Adding the value to sum
    }

    if (values.GetSize() == 0)
    {
        return 0.0f;
    }

    // Use the method calculateMeanForSPCCandMAD to get the mean
    float mean = calculateMeanForSPCCandMAD(values);
    float sumOfDeviations = 0.0f;

    // Calculate the sum of absolute deviations from the mean
    for (int i = 0; i < values.GetSize(); ++i)
    {
        float deviation = values[i] - mean;
        float finalDeviation = 0.0f;


        if (deviation < 0)
        {
            finalDeviation = deviation * -1;  // Multiplying by -1 to convert negative to positive
        }
        else
        {
            finalDeviation = deviation;  // If deviation is positive or zero, it remains unchanged
        }

        sumOfDeviations = sumOfDeviations + finalDeviation;
    }


    return sumOfDeviations / values.GetSize();
}
