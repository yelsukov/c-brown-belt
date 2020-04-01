#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int premutate() {
    uint16_t N;
    cin >> N;
    vector<int> v (N);
    iota (rbegin(v), rend(v), 1);
    do {
        for (auto& e : v) {
            cout << e << " ";
        }
        cout << endl;
    } while(prev_permutation(v.begin(), v.end()));

    return 0;
}