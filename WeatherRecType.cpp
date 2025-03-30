#include "WeatherRecType.h"


WeatherRecType::WeatherRecType()
{
    m_speed=0.0;
}

void WeatherRecType::GetDate(Date & date) const
{
    date = m_date; //return by reference date object


}
void WeatherRecType::SetDate(const Date & date)
{

    m_date = date; // set date object

}
void WeatherRecType::GetTime(Time & time) const
{
    time = m_time; //return by reference time object


}
void WeatherRecType::SetTime(const Time & time)
{

    m_time = time; // set time object

}
float WeatherRecType::GetSpeed() const
{
    return m_speed; //return wind speed
}
void WeatherRecType::SetSpeed(float speed)
{
    m_speed = speed; //Set wind speed

}

float WeatherRecType::GetTemperature() const
{
    return m_temperature; //return wind speed
}
void WeatherRecType::SetTemperature(float temperature)
{
    m_temperature = temperature; //Set wind speed

}

float WeatherRecType::GetSolarRadiation() const
{
    return m_solarRadiation; //return wind speed
}
void WeatherRecType::SetSolarRadiation(float solarRadiation)
{
    m_solarRadiation = solarRadiation; //Set wind speed

}


//Overload output stream to print weather objects
ostream & operator<<(ostream & os, const WeatherRecType & weatherRecType)
{
    Time tempTime;
    Date tempDate;
    weatherRecType.GetTime(tempTime);
    weatherRecType.GetDate(tempDate);


    //Print weather object details by using Get methods
    os << "Date            :" << tempDate <<'\n'
       << "Time            :" << tempTime << '\n'
       << "Wind Speeed     :" <<weatherRecType.GetSpeed() << '\n'
       << "Temperature     :"<<weatherRecType.GetTemperature() << '\n'
       << "Solar Radiation :"<<weatherRecType.GetSolarRadiation() << '\n';


    return os;
}
