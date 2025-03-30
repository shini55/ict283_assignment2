#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>
#include <string>

using std::string;
using std::ostream;

/**
 * @class Time
 * @brief A class that represents time in hours, minutes, and seconds.
 *
 * This class allows to store and helps in
 * getting and setting the hour, minute, and second attributes.
 */

class Time
{
public:

    /**
    * @brief Default constructor for the Time class.
    *
    * Initializes the time to 00:00:00 (midnight).
    */
    Time();

    /**
     * @brief Constructor to initialize the Time class with specific hour, minute, and second.
     *
     * @param hour The hour data
     * @param minute The minute data
     * @param second The second data
     */

    Time(int hour, int minute, int second);


    /**
     * @brief Getter for the hour.
     *
     * @return The hour of the time object.
     */
    int GetHour() const;
    /**
     * @brief Setter for the hour.
     *
     * @param hour The new hour value to set (0-23).
     */
    void SetHour(int hour);


    /**
     * @brief Getter for the minute.
     *
     * @return The minute of the time object.
     */
    int GetMinute() const;

    /**
     * @brief Setter for the minute.
     *
     * @param minute The new minute value to set (0-59).
     */
    void SetMinute(int minute);


    /**
     * @brief Getter for the second.
     *
     * @return The second of the time object.
     */
    int GetSecond() const;
    /**
    * @brief Setter for the second.
    *
    * @param second The new second value to set (0-59).
    */
    void SetSecond(int second);

private:
    int m_hour;    /// The hour data of time object
    int m_minute;  /// The minute data of time object
    int m_second;  /// The seconds data of time object
};


/**
 * @brief Overloaded output stream operator to print a Time object.
 *
 * This function helps to outputs the hour, minute, and seconds
 *
 * @param os The output stream.
 * @param time The Time object to be printed.
 * @return The output stream.
 */
ostream& operator << (ostream & os, const Time & time);

#endif // TIME_H_INCLUDED
