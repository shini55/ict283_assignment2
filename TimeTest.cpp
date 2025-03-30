#include "Time.h"
#include <iostream>


int main()
{


    Time myTime; //create time object

    //Test set methods
    myTime.SetHour(12);
    myTime.SetMinute(12);
    myTime.SetSecond(20);

    //Test and print get methods
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 1     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Hour: " << myTime.GetHour()<< std::endl;
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 2     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout<< "Minute : " << myTime.GetMinute() << std::endl;
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 3     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Second:" << myTime.GetSecond() << std::endl;


    return 0;
}
