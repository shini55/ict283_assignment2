#include <string>
#include <iostream>
#include <fstream>
#include "WeatherLogType.h"


int main()
{
    // 0. Data Store
    WeatherLogType weatherRecords;



    //1. Input/Load
    std::string csvFileName;
    int recordsLoaded = weatherRecords.LoadRecords(csvFileName);

    if (recordsLoaded < 0)
    {
        std::cout << "Error loading records. Exiting program." << std::endl;
        return 1;
    }

    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    std::cout << "*               WeatherLogType Collection               * " << std::endl;
    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "          SELECT A CHOICE LISTED BELOW TO BEGIN     " << std::endl;
    std::cout <<  "          -------------------------------------    " << std::endl;
    std::cout << "" << std::endl;

    //Intialise variable
    int choice = 0;
    int month = 1;
    int year =1909;


    //2. Process // 3.Output
    do
    {
        std::cout << ""<< std::endl;
        std::cout << "1: Display Average wind speed and sample standard deviation" << std::endl;
        std::cout << "2: Display Average ambient air temperature and sample standard deviation" << std::endl;
        std::cout << "3: Display Total solar radiation in kWh/m2" << std::endl;
        std::cout << "4: Output Average wind speed (km/h),average ambient air temperature and total solar radiation in kWh/m2" << std::endl;
        std::cout << "5: Exit Program" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Enter your choice: ";

        std::cin >> choice;


        switch (choice)
        {
        case 1:
        {
            std::cout << ""<< std::endl;
            std::cout << "Enter month: ";
            std::cin >> month;
            std::cout << "Enter year: ";
            std::cin >> year;
            std::cout << ""<< std::endl;
            weatherRecords.printAverageAndStdDevToScreen(choice, year, month);
            break;
        }
        case 2:
        {
            std::cout << ""<< std::endl;
            std::cout << "Enter year: ";
            std::cin >> year;
            std::cout << ""<< std::endl;
            weatherRecords.printAverageAndStdDevToScreen(choice, year, 0);
            break;
        }
        case 3:
        {
            std::cout << ""<< std::endl;
            std::cout << "Enter year: ";
            std::cin >> year;
            std::cout << ""<< std::endl;
            weatherRecords.printAverageAndStdDevToScreen(choice, year, 0);
            break;
        }
        case 4:
        {
            std::cout << "" << std::endl;
            std::cout << "Enter year: ";
            std::cin >> year;
            weatherRecords.printAverageAndTotalToFile(choice, year, 0);
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "Your Requested data is outputted to WindTempSolar.csv!" << std::endl;
            std::cout << "--------------------------------------------------------"  << std::endl;
            break;
        }
        case 5:

            std::cout << ""<< std::endl;
            std::cout << "Exiting program..." << std::endl;
            std::cout << ""<< std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "  Thank you for using WeatherLog Collection Program " << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;
            break;

        default:

            std::cout << "";
            std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
            break;
        }

    }
    while (choice != 5);

    std::cout << ""<< std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~ End of Program ~~~~~~~~~~~~~~~~~~~~" << std::endl;

    return 0;
}
