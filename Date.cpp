#include "Date.h"

//Default Constructor and initialize date to be 1/1/2000
Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 2000;
    m_dateFormatter.SetDay(m_day);
    m_dateFormatter.SetMonth(m_month);
    m_dateFormatter.SetYear(m_year);
}
Date::Date(int day, int month, int year)
{
    m_day =day;
    m_month=month;
    m_year=year;
    m_dateFormatter.SetDay(m_day);
    m_dateFormatter.SetMonth(m_month);
    m_dateFormatter.SetYear(m_year);
}

int Date::GetDay() const
{
    return m_day; // return day of the date
}

void Date::SetDay(int day)
{
    m_day = day; // set day of the date
    m_dateFormatter.SetDay(day);
}


int Date::GetMonth() const
{
    return m_month; // return month of the date
}

void Date::SetMonth(int month)
{
    m_month = month; // set month of the date
    m_dateFormatter.SetMonth(month);
}

int Date::GetYear() const
{
    return m_year; // return year of the date
}

void Date::SetYear(int year)
{
    m_year = year; // set year of the date
    m_dateFormatter.SetYear(year);
}

void Date::GetDateFormatter(DateFormatter & dateFormatter) const
{
    dateFormatter = m_dateFormatter; //return date formatter object
}

void Date::SetDateFormatter(const DateFormatter & dateFormatter)
{

    m_dateFormatter = dateFormatter; //set date formatter object

}


//Overload input stream to print unit objects
ostream& operator<<(ostream& os, const Date& date)
{

    DateFormatter tempFormatter; //initialize date formatter object
    date.GetDateFormatter(tempFormatter); //Pass date formatter object to Get method

    //Print date formatter object
    os << tempFormatter ;
    return os;


}
