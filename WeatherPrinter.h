#ifndef WEATHERPRINTER_H_INCLUDED
#define WEATHERPRINTER_H_INCLUDED

#include "WeatherLogType.h"
#include "Statistics.h"

class WeatherPrinter {
public:
    WeatherPrinter();
    WeatherPrinter(const WeatherLogType& weatherLog);
    ~WeatherPrinter();

    void printToScreen(const WeatherLogType& weatherLog, int choice, int year, int month) const;
    void printToFile(const WeatherLogType& weatherLog, int choice, int year, int month) const;

private:
    Statistics stats;
};

#endif // WEATHERPRINTER_H_INCLUDED
