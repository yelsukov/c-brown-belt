#pragma  once

#include <iostream>
#include <istream>

using namespace std;

/**
 * Class for interaction with date
 */
class Date {
public:
    uint GetYear() const;

    uint GetMonth() const;

    uint GetDay() const;

    uint64_t GetTimestamp() const;

    Date(uint year, uint month, uint day);

protected:
    uint year = 0;
    uint month = 0;
    uint day = 0;
    uint64_t timestamp = 0;
};


ostream &operator<<(ostream &stream, const Date &dt);

istream &operator>>(istream &stream, Date &dt);

bool operator<(const Date &lhs, const Date &rhs);

bool operator<=(const Date &lhs, const Date &rhs);

bool operator==(const Date &lhs, const Date &rhs);

Date ParseDate(istream &is);