#include <vector>
#include <algorithm>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    size_t th = (range_end - range_begin) / 3;
    if (th < 1) {
        return;
    }

    vector<typename RandomIt::value_type> elements{range_begin, range_end};
    RandomIt first_th = elements.begin() + th,
            second_th = first_th + th;

    MergeSort(elements.begin(), first_th);
    MergeSort(first_th, second_th);
    MergeSort(second_th, elements.end());

    vector<typename RandomIt::value_type> tmp;
    merge(elements.begin(), first_th, first_th, second_th, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), second_th, elements.end(), range_begin);
}