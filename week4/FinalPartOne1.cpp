#include <iostream>
#include <string>
#include <deque>

using namespace std;


int main() {
    int x;
    cin >> x;
    size_t N;
    cin >> N;

    deque<string> res{to_string(x)};
    while (N >= 1) {
        string op;
        getline(cin, op, '\n');
        if (op.empty()) {
            continue;
        }
        res.push_front("(");
        res.push_back(") " + op);
        --N;
    }

    for (const string& s : res) {
        cout << s;
    }

    return 0;
}

//int main() {
//    int x;
//    cin >> x;
//    size_t N;
//    cin >> N;
//
//    deque<string> res{"(" + to_string(x) + ")"};
//    for (size_t i = 0; i < N; ++i) {
//        char op;
//        int d;
//        cin >> op >> d;
//        res.push_back(string(1, ' ') + op + " " + to_string(d));
//        if (i != (N - 1)) {
//            res.push_front("(");
//            res.push_back(")");
//        }
//    }
//
//    for (const string& s : res) {
//        cout << s;
//    }
//
//    return 0;
//}