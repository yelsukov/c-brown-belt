#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
    return {find_if(elements.begin(), elements.end(), [border](T e) { return e > border; }), elements.end()};
}