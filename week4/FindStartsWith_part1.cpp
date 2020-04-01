#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    char next_char = static_cast<char>(prefix + 1);
    return {
            lower_bound(range_begin, range_end, string(1, prefix)),
            lower_bound(range_begin, range_end, next_char)
    };
}