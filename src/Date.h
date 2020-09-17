#pragma once

#include <iostream>
#include <ctime>

class Date {
private:
    std::tm date_;
    static time_t badTime();
    std::time_t dateToTime() const;
public:
    static int daysInMonth[12];
    Date(int day, int month, int year);
    Date operator - (const int &days);
    Date operator + (const int &days);
    friend std::ostream& operator<<(std::ostream& os, const Date &dt);
    void setDate(int day, int month, int year);
    long daysUntil(const Date &dt);
};

int Date::daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

Date::Date(int day, int month, int year) : date_(tm()) {
    if (day > 0 && day < 32) date_.tm_mday = day;
    if (month > 0 && month < 13) date_.tm_mon = month;
    if (year > 1970 && year < 2030) date_.tm_year = year;
}


std::ostream& operator<<(std::ostream &os, const Date &dt) {
    os << dt.date_.tm_mday << "/" << dt.date_.tm_mon << "/" << dt.date_.tm_year;
    return os;
}

void Date::setDate(int day, int month, int year) {
    if (day > 0 && day < 32) date_.tm_mday = day;
    if (month > 0 && month < 13) date_.tm_mday= month;
    if (year > 1970 && year < 2030) date_.tm_mday = year;
}

std::time_t Date::dateToTime() const {
    tm tmp = tm();
    tmp.tm_mday = date_.tm_mday;
    tmp.tm_mon = date_.tm_mon - 1;
    tmp.tm_year = date_.tm_year - 1900;
    return mktime(&tmp);
}

std::time_t Date::badTime() {
    return time_t(-1);
}



Date Date::operator-(const int &days) {
    date_.tm_mday -= days;
    while (date_.tm_mday < 0) {
        int leftOver = date_.tm_mday;
        if (date_.tm_mon > 1) date_.tm_mon -= 1;
        else {
            date_.tm_mon = 12;
            date_.tm_year -= 1;
        }
        date_.tm_mday = daysInMonth[date_.tm_mon - 1];
        date_.tm_mday += leftOver;
    }

    return *this;
}

Date Date::operator+(const int &days) {
    date_.tm_mday += days;
    while (date_.tm_mday > daysInMonth[date_.tm_mon - 1]) {
        int leftOver = date_.tm_mday - daysInMonth[date_.tm_mon];
        if (date_.tm_mon < 11) date_.tm_mon += 1;
        else {
            date_.tm_mon = 1;
            date_.tm_year += 1;
        }
        date_.tm_mday = 1;
        date_.tm_mday += leftOver;
    }
    return *this;
}

long Date::daysUntil(const Date &dt) {
    std::time_t thisTime = this->dateToTime();
    std::time_t rhsTime = dt.dateToTime();

    if (thisTime == badTime() || rhsTime == badTime()) {
        std::cout << "Unable to create correct time from one of the dates";
        return 1;
    }
    double sec = std::difftime(thisTime, rhsTime);
    long days = static_cast<long>(sec / (60 * 60 * 24));
    return days;
}



// 10/12/20 ---- 5/10/21