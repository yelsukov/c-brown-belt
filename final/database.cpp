#include "database.h"

#include <iostream>
#include <sstream>

void Database::Add(const Date &date, const string &event) {
    auto res = this->storage[date].first.insert(event);
    if (res.second) { //real insert completed then insert into storage
        this->storage[date].second.push_back(event);
    }
}

string Database::Last(const Date &date) const {
    if (this->storage.empty() || date < this->storage.begin()->first) {
        return "No entries";
    }

    auto it = this->storage.upper_bound(date);
    --it;

    ostringstream s;
    s << it->first << " " << it->second.second.back();

    return s.str();
}

void Database::Print(ostream &os) const {
    for (const auto &item : this->storage) {
        for (const auto &event : item.second.second) {
            os << item.first << " " << event << endl;
        }
    }
}