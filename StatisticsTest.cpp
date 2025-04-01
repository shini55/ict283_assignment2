#include <iostream>
#include "Statistics.h"
#include "WeatherRecType.h"
#include "Map.h"  // Include your Map class header
#include "Vector.h"

using namespace std;

// Using your custom Map class for weather data structure
typedef Map<int, Map<int, Vector<WeatherRecType>>> WeatherDataMap;

int main() {
    // Step 1: Create the weather data structure using your custom Map
    WeatherDataMap weatherData;

    // Step 2: Insert sample data for year 2025, month 1
    Vector<WeatherRecType> januaryRecords;

    WeatherRecType record1, record2, record3;

    // Set sample data for the records
    record1.SetSpeed(5.0);
    record1.SetTemperature(25.0);
    record1.SetSolarRadiation(120.0);

    record2.SetSpeed(7.5);
    record2.SetTemperature(26.5);
    record2.SetSolarRadiation(140.0);

    record3.SetSpeed(6.0);
    record3.SetTemperature(24.5);
    record3.SetSolarRadiation(130.0);

    // Add records to the vector using proper insertion
    januaryRecords.Insert(record1, 0);  // Insert at index 0
    januaryRecords.Insert(record2, 1);  // Insert at index 1
    januaryRecords.Insert(record3, 2);  // Insert at index 2

    // Insert the vector into the nested map (year -> month -> records)
    weatherData.add(2025, Map<int, Vector<WeatherRecType>>());  // Add entry for 2025
    weatherData.get(2025).add(1, januaryRecords);  // Add records for January 2025

    // Step 3: Create Statistics object
    Statistics stats(weatherData);

    // Step 4: Test the Statistics methods
    cout << "Average Wind Speed (km/h): " << stats.calculateAverage(0, 2025, 1) << endl;
    cout << "Average Temperature (C): " << stats.calculateAverage(1, 2025, 1) << endl;
    cout << "Average Solar Radiation: " << stats.calculateAverage(2, 2025, 1) << endl;

    cout << "Standard Deviation of Wind Speed: " << stats.calculateStandardDeviation(0, 2025, 1) << endl;
    cout << "Standard Deviation of Temperature: " << stats.calculateStandardDeviation(1, 2025, 1) << endl;

    cout << "Total Solar Radiation (kWh/m2): " << stats.calculateTotalSolarRadiation(2025, 1) << endl;

    // Step 5: Test SPCC calculations
    cout << "SPCC (Wind Speed & Temperature): " << stats.calculateSPCC(0, 2025, 1) << endl;
    cout << "SPCC (Wind Speed & Solar Radiation): " << stats.calculateSPCC(1, 2025, 1) << endl;
    cout << "SPCC (Temperature & Solar Radiation): " << stats.calculateSPCC(2, 2025, 1) << endl;

    // Step 6: Test MAD calculations
    cout << "MAD for Wind Speed: " << stats.calculateMAD(0, 2025, 1) << endl;
    cout << "MAD for Temperature: " << stats.calculateMAD(1, 2025, 1) << endl;

    return 0;
}
