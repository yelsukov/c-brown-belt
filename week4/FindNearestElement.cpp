#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border) {
    if (numbers.empty()) {
        return numbers.end();
    }

    auto last_it = prev(numbers.end());
    if (*last_it <= border) {
        return last_it;
    }

    auto it = numbers.lower_bound(border);
    auto prev_it = it != numbers.begin() ? prev(it) : it;

    return border - *prev_it > *it - border ? it : prev_it;
}
