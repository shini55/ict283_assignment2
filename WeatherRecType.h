#ifndef WEATHERRECTYPE_H_INCLUDED
#define WEATHERRECTYPE_H_INCLUDED
#include "Date.h"
#include "Time.h"

/**
 * @class WeatherRecType
 * @brief A class that represents a weather record containing date, time, wind speed, temperature, and solar radiation.
 */

class WeatherRecType
{
public:

    /**
     * @brief Default constructor for WeatherRecType.
     */
    WeatherRecType();


    /**
     * @brief Gets the date of the weather record.
     * @param date Reference to a Date object where the retrieved date will be stored.
     */
    void GetDate(Date & date) const;

    /**
    * @brief Sets the date of the weather record.
    * @param date The Date object to set.
    */
    void SetDate(const Date & date);



    /**
     * @brief Gets the time of the weather record.
     * @param time Reference to a Time object where the retrieved time will be stored.
     */
    void GetTime(Time & time) const;
    /**
     * @brief Sets the time of the weather record.
     * @param time The Time object to set.
     */
    void SetTime(const Time & time);



    /**
     * @brief Gets the wind speed.
     * @return The wind speed as a float.
     */
    float GetSpeed() const;
    /**
     * @brief Sets the wind speed.
     * @param speed The wind speed to set.
     */
    void SetSpeed(float speed);




    /**
     * @brief Gets the temperature.
     * @return The temperature as a float.
     */
    float GetTemperature() const;
    /**
     * @brief Sets the temperature.
     * @param temperature The temperature to set.
     */
    void SetTemperature(float temperature);



    /**
    * @brief Gets the solar radiation value.
    * @return The solar radiation as a float.
    */
    float GetSolarRadiation() const;

    /**
    * @brief Sets the solar radiation value.
    * @param solarRadiation The solar radiation value to set.
    */
    void SetSolarRadiation(float solarRadiation);




private:

    Date m_date; /// The date of the weather record.
    Time m_time; /// The time of the weather record.
    float m_speed; /// The wind speed.
    float m_temperature; /// The temperature.
    float m_solarRadiation; /// The solar radiation value.
};


/**
 * @brief Overloaded output stream operator to print a WeatherRecType object.
 *
 * This function helps to outputs the date,time,speed,temperature,solar radiation
 *
 * @param os The output stream.
 * @param weatherRecType The weatherRecType object to be printed.
 * @return The output stream.
 */

ostream & operator <<( ostream & os, const WeatherRecType & weatherRecType );

#endif // WEATHERRECTYPE_H_INCLUDED
