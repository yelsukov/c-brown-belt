#include "date.h"

#include <vector>
#include <iomanip>

uint Date::GetYear() const {
    return this->year;
}

uint Date::GetMonth() const {
    return this->month;
}

uint Date::GetDay() const {
    return this->day;
}

uint64_t Date::GetTimestamp() const {
    return this->timestamp;
}


Date::Date(uint year, uint month, uint day) {
    if (month <= 0 || month > 12) {
        throw invalid_argument("Month value is invalid: " + to_string(month));
    }
    if (day <= 0 || day > 31) {
        throw invalid_argument("Day value is invalid: " + to_string(day));
    }

    this->year = year;
    this->month = month;
    this->day = day;

    uint64_t dt = 24 * 3600, mt = dt * 31, yt = 12 * mt;
    this->timestamp = (this->year * yt) + (this->month * mt) + (this->day * dt);
}

ostream &operator<<(ostream &stream, const Date &dt) {
    stream << setfill('0')
           << setw(4) << dt.GetYear() << '-'
           << setw(2) << dt.GetMonth() << '-'
           << setw(2) << dt.GetDay();

    return stream;
}

istream &operator>>(istream &stream, Date &dt) {
    string date;
    stream >> date;

    stringstream inner(date);

    uint year = 0, month = 0, day = 0;
    inner >> year;
    inner.ignore(1);
    inner >> month;
    inner.ignore(1);
    inner >> day;
    if (!inner || !inner.eof()) {
        throw invalid_argument("Wrong date format: " + date);
    }

    dt = Date(year, month, day);

    return stream;
}

bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.GetTimestamp() == rhs.GetTimestamp();
}

bool operator<(const Date &lhs, const Date &rhs) {
    return lhs.GetTimestamp() < rhs.GetTimestamp();
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return lhs.GetTimestamp() <= rhs.GetTimestamp();
}

Date ParseDate(istream &is) {
    uint year = 0, month = 0, day = 0;
    char dash;
    is >> year >> dash >> month >> dash >> day;
    return {year, month, day};
}