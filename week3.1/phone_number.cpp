#include "phone_number.h"

#include <sstream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream ss(international_number);
    string delimiter;

    char plus = ss.get();
    getline(ss, this->country_code_, '-');
    getline(ss, this->city_code_, '-');
    getline(ss, this->local_number_);
    if (plus != '+' || this->country_code_.empty() || this->city_code_.empty() || this->local_number_.empty()) {
        throw invalid_argument("Invalid phone number");
    }
}

string PhoneNumber::GetCountryCode() const {
    return this->country_code_;
}

string PhoneNumber::GetCityCode() const {
    return this->city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return this->local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + this->country_code_ + '-' + this->city_code_ + '-' + this->local_number_;
}