#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;


int main() {
    int x;
    cin >> x;
    size_t N;
    cin >> N;

    deque<string> result {to_string(x)};
    char prev_op;
    for (size_t i = 0; i <= N; ++i) {
        string op;
        getline(cin, op, '\n');
        if (op.empty()) {
            continue;
        }
        if ((prev_op == '-' || prev_op == '+') && (op[0] == '*' || op[0] == '/')) {
            result.push_front("(");
            result.push_back(")");
        }
        result.push_back(" " + op);
        prev_op = op[0];
    }

    for (const string& s : result) {
        cout << s;
    }

    return 0;
}