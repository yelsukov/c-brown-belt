#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto it = find_if(numbers.begin(), numbers.end(), [](const int& v) {
        return v < -0;
    });

    while(it != numbers.begin()) {
        cout << *(--it) << " ";
    }
}
