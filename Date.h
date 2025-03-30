#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

#include "DateFormatter.h"

/**
 * @class Date
 * @brief A class to represent a date consisting of a day, month, and year.
 *
 * This class stores a date and provides methods to access and modify day,month and year of a date
 */

class Date
{

public:


    /**
    * @brief Default constructor.
    *
    * Initializes the day, month, and year
    */
    Date();


    /**
    * @brief Constructor that initializes a date with the specified day, month, and year.
    *
    * @param day The day of the date.
    * @param month The month of the date.
    * @param year The year of the date.
    */
    Date(int day, int month, int year);


    /**
     * @brief Gets the day of the date.
     *
     * @return The day as an integer.
     */

    int GetDay() const;
    /**
     * @brief Sets the day of the date.
     *
     * @param day The day to set.
     */
    void SetDay(int day);


    /**
    * @brief Gets the month of the date.
    *
    * @return The month as an integer (1-12).
    */
    int GetMonth() const;

    /**
     * @brief Sets the month of the date.
     *
     * @param month The month to set (1-12).
     */
    void SetMonth(int month);


    /**
     * @brief Gets the year of the date.
     *
     * @return The year as an integer.
     */
    int GetYear() const;
    /**
     * @brief Sets the year of the date.
     *
     * @param year The year to set.
     */
    void SetYear(int year);


    /**
     * @brief Gets the `DateFormatter` object associated with the date.
     *
     * @param dateFormatter A reference to a `DateFormatter` object where the formatted date will be stored.
     */

    void GetDateFormatter(DateFormatter & dateFormatter) const;

    /**
     * @brief Sets the `DateFormatter` object for this date.
     *
     * @param dateFormatter The `DateFormatter` object to associate with the date.
     */
    void SetDateFormatter(const DateFormatter & dateFormatter);



private:
    int m_day;      /// The day of the date
    int m_month;    /// The month of the date
    int m_year;     /// The year of the year
    DateFormatter m_dateFormatter; ///Dateformatter object

};

/**
 * @brief Overloaded output stream operator to print a Date object.
 *
 * This function helps to outputs the day, month, and year
 *
 * @param os The output stream.
 * @param date The Date object to be printed.
 * @return The output stream.
 */
ostream & operator <<( ostream & os, const Date & date );

#endif // DATE_H_INCLUDED
