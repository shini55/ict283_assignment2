#ifndef DATEFORMATTER_H_INCLUDED
#define DATEFORMATTER_H_INCLUDED

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;


/**
 * @class DateFormatter
 * @brief A class to manage and format dates.
 *
 * This class stores the day, month, and year as integers, and provides
 * methods to retrieve and modify these values.
 */
class DateFormatter
{
public:

    /**
    * @brief Default constructor.
    *
    * Initializes the day, month, and year to default values (e.g., 0).
    */
    DateFormatter();

    /**
    * @brief Constructor that initializes a date with the specified day, month, and year.
    *
    * @param day The day of the date.
    * @param month The month of the date.
    * @param year The year of the date.
    */
    DateFormatter(int day, int month, int year);


    /**
     * @brief Gets the day of the date.
     *
     * @return The day as an integer.
     */
    int GetDay() const;
    /**
    * @brief Sets the day of the date.
    *
    * @param day The day to be set.
    */
    void SetDay(int day);


    /**
     * @brief Gets the month of the date.
     *
     * @param month A reference to a string where the month will be stored.
     */
    void GetMonth(string & month) const;
    /**
    * @brief Sets the month of the date.
    *
    * @param month The month to be set as an integer (1-12).
    */
    void SetMonth(int month);


    /**
     * @brief Sets the year of the date.
     *
     * @param year The year to be set.
     */
    void SetYear(int year);

    /**
    * @brief Gets the year of the date.
    *
    * @return The year as an integer.
    */
    int GetYear() const;


private:

    int m_day;  ///The day of the date
    int m_month; ///The month of the date
    int m_year;  ///The year of the date


};


/**
 * @brief Overloaded output stream operator to print a DateFormatter object.
 *
 * This function helps print the date after being formatted
 *
 * @param os The output stream.
 * @param dateFormatter The DateFormatter object to be printed.
 * @return The output stream.
 */
ostream & operator <<( ostream & os, const DateFormatter & dateFormatter );

#endif // DATEFORMATTER_H_INCLUDED
