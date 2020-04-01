#include <vector>
#include <algorithm>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    size_t size = range_end - range_begin;
    if (size < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements{range_begin, range_end};
    RandomIt mid = elements.begin() + (size / 2);
    MergeSort(elements.begin(), mid);
    MergeSort(mid, elements.end());
    merge(elements.begin(), mid, mid, elements.end(), range_begin);
}