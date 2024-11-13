// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include "date.h"
#include <iomanip>
#include <sstream>
// Provided default constructor to create an unitialised date.
Date::Date() : year(0), month(0), day(0), initialized(false) {}

// TODO write a function setDateFromString that takes a string argument in
// "YYYY-MM-DD" format and sets the appropriate member variables (year, month,
// day, and initialised). If dateString is empty reset the object to its
// uninitialised state (see default constructor). If dateString is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date();
//  d.setDateString("2024-01-01");
void Date::setDateFromString(std::string dString)
{
    std::vector<std::string> splitStrings;
    std::stringstream dStringStrm(dString);
    std::string tempSplitString;

    if (dString.length() == 0)
    {
        unInitialise();
        return;
    }

    // Check if the length is correct
    if (dString.length() > 10)
    {
        unInitialise();
        throw std::invalid_argument("Invalid date string length - must be YYYY-MM-DD");
    }

    // While there are still splits we can make,
    // split this string wherever an - character appears,
    // store the resulting string in a temporary variable,
    // then push that temporary variable onto a vector's stack.
    while (std::getline(dStringStrm, tempSplitString, '-'))
    {
        splitStrings.push_back(tempSplitString);
    }

    // Check if all date fields were provided
    if (splitStrings.size() != 3)
    {
        unInitialise();
        throw std::invalid_argument("Invalid date string split - must be YYYY-MM-DD");
    }

    // Check the lengths of each date field
    if (splitStrings[0].length() != 4)
    {
        unInitialise();
        throw std::invalid_argument("Invalid year - must be YYYY-MM-DD");
    }

    if (splitStrings[1].length() != 2 || std::stoi(splitStrings[1]) > 12)
    {
        throw std::invalid_argument("Invalid month - must be YYYY-MM-DD");
    }

    if (splitStrings[2].length() != 2)
    {
        unInitialise();
        throw std::invalid_argument("Invalid day - must be YYYY-MM-DD");
    }

    unsigned int pYear = 0;
    unsigned int pMonth = 0;
    unsigned int pDay = 0;

    try
    {
        // Parse the values
        pYear = (unsigned int) std::stoi(splitStrings[0]);
        pMonth = (unsigned int) std::stoi(splitStrings[1]);
        pDay = (unsigned int) std::stoi(splitStrings[2]);
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("Invalid date string");
    }

    // Check the year, and consequently the character length at the same time
    if (pYear > 9999 || pYear < 1900)
        throw std::invalid_argument("Invalid year");

    if (pMonth > 12 || pMonth < 1)
        throw std::invalid_argument("Invalid month");

    // Check whether the number of days corresponds to the given month
    if (pMonth == 4 || pMonth == 6 || pMonth == 9 || pMonth == 11)
    {
        if (pDay < 1 || pDay > 30)
        {
            throw std::invalid_argument("Invalid day");
        }
    }

    if (pMonth == 1 || pMonth == 3 || pMonth == 5 || pMonth == 7 || pMonth == 8 || pMonth == 10 || pMonth == 12)
    {
        if (pDay < 1 || pDay > 31)
        {
            throw std::invalid_argument("Invalid day");
        }
    }

    if (pMonth == 2)
    {
        if (pDay < 1 || pDay > 28)
        {
            throw std::invalid_argument("Invalid day");
        }
    }

    year = pYear;
    month = pMonth;
    day = pDay;
    initialized = true;

}

void Date::unInitialise() noexcept
{
    year = 0;
    month = 0;
    day = 0;
    initialized = false;
}

// TODO Write a function, isInitialised, that takes no parameters and returns true
//  if the Date object is initialised, and false if it is NOT initialised.
// Example:
//  Date d = Date();
//  if(d.isInitialised()) {
//    ...
//  }
const bool &Date::isInitialised() const noexcept
{
    return initialized;
}

// TODO Write a function, str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  If the
// Date object is NOT initialised, return an empty string.
// Example:
//  Date d = Date();
//  d.setDate(2024,1,1);
//  std::cout << d.str() << std::endl;
std::string Date::str() const
{
    std::stringstream sstream;

    if (isInitialised())
    {
        sstream << "\"" << year << "-"
                << std::setfill('0') << std::setw(2) << month
                << std::setfill(' ') << std::setw(1) << "-"
                << std::setfill('0') << std::setw(2) << day << "\"";
    }
    else
    {
        return (std::string) "";
    }

    return sstream.str();
}

// TODO create a function, setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters and also
// sets the initilized flag.
// Example:
//  Date d = Date();
//  d.setDate(2024, 1, 1);
void Date::setDate(unsigned int nYear, unsigned int nMonth, unsigned int nDay) noexcept
{
    year = nYear;
    month = nMonth;
    day = nDay;
    initialized = true;
}

// TODO Write a function, getYear, that takes no parameters and returns year
// member variable
//  Date d = Date();
//  auto year = d.getYear();
const unsigned int &Date::getYear() const noexcept
{
    return year;
}

// TODO Write a function, getMonth, that takes no parameters and returns month
// member variable
//  Date d = Date();
//  auto month = d.getMonth();
const unsigned int &Date::getMonth() const noexcept
{
    return month;
}

// TODO Write a function, getDay, that takes no parameters and returns day
// member variable
//  Date d = Date();
//  auto day = d.getDay();
const unsigned int &Date::getDay() const noexcept
{
    return day;
}

// TODO Write an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example
//  Date d1 = Date();
//   d1.setDate(2024, 1, 1);
//   Date d2 = Date();
//   d2.setDate(2024, 1, 2);
//   if (d1 == d2) {
//     ...
//   }
bool operator==(const Date &d1, const Date &d2)
{
    return ((d1.getYear() == d2.getYear()) 
            && (d1.getYear() == d2.getYear())
            && (d1.getMonth() == d2.getMonth())
            && (d1.getDay() == d2.getDay()));
}

// TODO Write an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. Note: You can ignore the 'initialised' member
// variable when drawing the comparison.

//  Date d1 = Date();
//   d1.setDate(2024, 1, 1);
//   Date d2 = Date();
//   d2.setDate(2024, 1, 2);
//   if (d1 < d2) {
//     ...
//   }
bool operator<(const Date &d_lhs, const Date &d_rhs)
{

    bool firstDateEarlier = false;

    if (d_lhs.getYear() != d_rhs.getYear())
    {
        firstDateEarlier = d_lhs.getYear() < d_rhs.getYear();
    }

    else if (d_lhs.getMonth() != d_rhs.getMonth())
    {
        firstDateEarlier =  d_lhs.getMonth() < d_rhs.getMonth();
    }

    else if (d_lhs.getDay() != d_rhs.getDay())
    {
        firstDateEarlier =  d_lhs.getDay() < d_rhs.getDay();
    }

    return firstDateEarlier;

}
