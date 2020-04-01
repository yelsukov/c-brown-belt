#include <iostream>
#include <vector>
#include <set>

using namespace std;

template<typename T>
void RemoveDuplicates(vector<T> &elements) {
    set<T> tmp{elements.begin(), elements.end()};
    elements = {tmp.begin(), tmp.end()};
}