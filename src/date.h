// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// - initialised
//
// A Date object should only be set to initialised if it is a valid date.
// Otherwise it is should remain unintialised.
// -----------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include "lib_json.hpp"

class Date {
private:
    unsigned int year, month, day;
    bool initialized;

public:
    Date();

    const bool &isInitialised() const noexcept;
    const unsigned int &getYear() const noexcept;
    const unsigned int &getMonth() const noexcept;
    const unsigned int &getDay() const noexcept;
    std::string str() const;

    void setDateFromString(std::string dString);
    void setDate(unsigned int nYear, unsigned int nMonth, unsigned int nDay) noexcept;
    void unInitialise() noexcept;

    friend bool operator==(const Date &d1, const Date &d2);
    friend bool operator<(const Date &d_lhs, const Date &d_rhs);

};

#endif // DATE_H
