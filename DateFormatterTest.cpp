#include <iostream>
#include "DateFormatter.h"

int main()
{


    DateFormatter myDateFormatter;

    // Test set methods
    myDateFormatter.SetDay(10);
    myDateFormatter.SetMonth(12);
    myDateFormatter.SetYear(2025);

    // Test get methods
    int day = myDateFormatter.GetDay();
    int year = myDateFormatter.GetYear();
    std::string month;
    myDateFormatter.GetMonth(month);

    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 1     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Day: " << day << std::endl;
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 2     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout<< "Month : " << month << std::endl;
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 3     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Year:" << year << std::endl;



    return 0;
}
