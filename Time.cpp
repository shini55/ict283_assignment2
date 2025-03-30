#include "Time.h"
#include <iomanip>


Time::Time()
{
    m_hour = 0;
    m_minute = 0;
    m_second = 0;
}
//Parameter constructor of time object
Time::Time(int hour, int minute, int second)
{
    m_hour=hour;
    m_minute=minute;
    m_second=second;
}

int Time::GetHour() const
{
    return m_hour; // return hour of the time
}

void Time::SetHour(int hour)
{
    if (hour < 0 || hour > 23) // Ensure hour is within valid range (0-23)
    {
        m_hour = 0; // Set to 0 if invalid
    }
    else
    {
        m_hour = hour;
    }
}

int Time::GetMinute() const
{
    return m_minute; // return min of the time
}

void Time::SetMinute(int minute)
{
    if (minute < 0 || minute > 59) // Ensure minute is within valid range (0-59)
    {
        m_minute = 0; // Set to 0 if invalid
    }
    else
    {
        m_minute = minute;
    }
}

int Time::GetSecond() const
{
    return m_second; // return min of the time
}

void Time::SetSecond(int second)
{
    if (second < 0 || second > 59) // Ensure second is within valid range (0-59)
    {
        m_second = 0; // Set to 0 if invalid
    }
    else
    {
        m_second = second;
    }
}

//Overload input stream to print time  objects
ostream & operator <<( ostream & os, const Time & time )
{

    //Print time object details by using Get methods in 23:12:00 format
    os << std::setfill('0') <<std::setw(2)  << time.GetHour() << ":" << std::setw(2) << time.GetMinute() << ":"<< std::setw(2) << time.GetSecond();
    return os;
}


