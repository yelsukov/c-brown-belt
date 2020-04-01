#pragma once

#include "date.h"
#include <set>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Database {
public:
    void Add(const Date &date, const string &event);

    template<typename Func>
    int RemoveIf(Func predicate) {
        int cnt = 0;
        for (auto db_it = this->storage.begin(); db_it != this->storage.end();) {
            vector<string> *events = &db_it->second.second;

            auto e_begin = events->begin(), e_end = events->end();
            auto it_remove = stable_partition(e_begin, e_end, [db_it, predicate](const string &event) {
                return !predicate(db_it->first, event);
            });

            // Not found suitable rows for condition of removing
            if (it_remove == e_end) {
                db_it++;
                continue;
            }

            cnt += e_end - it_remove;

            if (e_begin != it_remove) {
                for (auto it = it_remove; it != e_end; ++it) {
                    db_it->second.first.erase(*it); // remove from indexes
                }
                events->erase(it_remove, e_end);
                db_it++;
            } else {
                this->storage.erase(db_it++);
            }
        }

        return cnt;
    }

    template<typename Func>
    vector<pair<Date, string>> FindIf(Func predicate) const {
        vector<pair<Date, string>> result;
        for (const auto &entry : this->storage) {
            for (const auto &event : entry.second.second) {
                if (predicate(entry.first, event)) {
                    result.push_back({entry.first, event});
                }
            }
        }

        return result;
    }

    string Last(const Date &date) const;

    void Print(ostream &os) const;

private:
    map<Date, pair<set<string>, vector<string>>> storage;
};

template<typename First, typename Second>
ostream &operator<<(ostream &os, const pair<First, Second> &p) {
    os << p.first << " " << p.second;
    return os;
}
