#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix) {
    auto first = lower_bound(range_begin, range_end, prefix);

    string s = prefix;
    s[s.size() - 1]++;
    auto last = lower_bound(range_begin, range_end, s);

    return {first, last};
}
