#include "Date.h"
#include <iostream>



int main()
{


    Date myDate;
    // Test setters and getters for date
    myDate.SetDay(20);
    myDate.SetMonth(12);
    myDate.SetYear(2023);

    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 1     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Day: " << myDate.GetDay() << std::endl;
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 2     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout<< "Month : " << myDate.GetMonth() << std::endl;
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 3     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Year:" << myDate.GetYear() << std::endl;

    //Test dateformatter object
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 4     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    DateFormatter dateFormatter;
    myDate.GetDateFormatter(dateFormatter);
    std::cout << dateFormatter << std::endl;


    return 0;
}
