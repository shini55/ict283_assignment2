#include <iostream>
#include "WeatherRecType.h"


int main()
{
    WeatherRecType myWeatherRecType;//Create weather rec object
    Date myDate;//create date object
    Time myTime;//create time object


    //Set Speed,Temp and solar Radiation

    myWeatherRecType.SetSpeed(8);
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 1     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Wind Speed :" << myWeatherRecType.GetSpeed() << std::endl;

    myWeatherRecType.SetTemperature(40.0);
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 2     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Temperature :" <<myWeatherRecType.GetTemperature() << std::endl;

    myWeatherRecType.SetSolarRadiation(200);
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 3     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Solar Radiation :" << myWeatherRecType.GetSolarRadiation() << std::endl;

    //Set date objects
    myDate.SetDay(20);
    myDate.SetMonth(12);
    myDate.SetYear(2023);
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 4     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Date :"<<myDate.GetDay() << "/" << myDate.GetMonth() << "/" << myDate.GetYear()<< std::endl;

    //Set Time objects
    myTime.SetHour(1);
    myTime.SetMinute(10);
    myTime.SetSecond(30);
    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 5     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Time:" << myTime.GetHour() << ":" << myTime.GetMinute() << ":" << myTime.GetSecond() << std::endl;

    //Parsed Date object
    myWeatherRecType.SetDate(myDate);

    //std::cout << myWeatherRecType.GetDate(myDate) << std::endl;//print weatherRecType

    //Parsed Time object
    myWeatherRecType.SetTime(myTime);

    std::cout << ""<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 6     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout <<"Print all Weather Records " <<std::endl;
    std::cout << ""<< std::endl;
    std::cout << myWeatherRecType << std::endl;//print weatherRecType





}
