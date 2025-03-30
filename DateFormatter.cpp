#include "DateFormatter.h"
#include <iomanip>
//Default Constructor and initialize date to be 1/1/2000
DateFormatter::DateFormatter()
{
    m_day=1;
    m_month =1;
    m_year=2000;

}

DateFormatter::DateFormatter(int day, int month, int year)
{
    m_day =day;
    m_month=month;
    m_year=year;
}


int DateFormatter::GetDay() const
{
    return m_day;// return day of the date
}

void DateFormatter::SetDay(int day)
{
    m_day = day; //set day of the date
}



void DateFormatter::GetMonth(string & month) const
{

    //Create an if/else check statement to check
    if (m_month == 1)
    {
        month = "January";
    }
    else if (m_month == 2)
    {
        month = "February";
    }
    else if (m_month == 3)
    {
        month = "March";
    }
    else if (m_month == 4)
    {
        month = "April";
    }
    else if (m_month == 5)
    {
        month = "May";
    }
    else if (m_month == 6)
    {
        month = "June";
    }
    else if (m_month == 7)
    {
        month = "July";
    }
    else if (m_month == 8)
    {
        month = "August";
    }
    else if (m_month == 9)
    {
        month = "September";
    }
    else if (m_month == 10)
    {
        month = "October";
    }
    else if (m_month == 11)
    {
        month = "November";
    }
    else if (m_month == 12)
    {
        month = "December";
    }
    else
    {
        month = "Invalid Date";
    }

}

void DateFormatter::SetMonth(int month)
{

    m_month=month;//set month of the date

}

int DateFormatter::GetYear() const
{
    return m_year; // return year of the date
}


void DateFormatter::SetYear(int year)
{
    m_year = year; //set year of the date
}

//Overload input stream to print date formatter objects
ostream & operator <<( ostream & os, const DateFormatter & dateFormatter )
{

    string month;
    dateFormatter.GetMonth(month);

    os << std::setfill('0') <<std::setw(2)  << dateFormatter.GetDay() << " " << std::setw(2) << month << " "<<  dateFormatter.GetYear();
    return os;

}



