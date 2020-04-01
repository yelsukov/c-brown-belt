#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
    if (a == 0) {
        return b != 0 ? 1 : 0;
    }

    double D = pow(b, 2) - 4 * a * c;
    return D > 0 ? 2 : (D == 0 ? 1 : 0);
}

void TestAllCases() {
    AssertEqual(GetDistinctRealRootCount(0, 1, 2), 1, "a == 0");
    AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0, "a == 0 && b == 0");
    AssertEqual(GetDistinctRealRootCount(0, 0, 0), 0, "a == 0 && b == 0 && c == 0");
    AssertEqual(GetDistinctRealRootCount(5, 0, 2), 0, "b == 0 && a > 0 && c > 0");
    AssertEqual(GetDistinctRealRootCount(-5, 0, 2), 2, "b == 0 && a < 0 && c > 0");
    AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "a == 1 && b == 2 && c == 1");
    AssertEqual(GetDistinctRealRootCount(1, 4, 1), 2, "a == 1 && b == 4 && c == 1");
    AssertEqual(GetDistinctRealRootCount(2, 2, 4), 0, "a == 2 && b == 2 && c == 4");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestAllCases, "TestAllCases");
    // добавьте сюда свои тесты
    return 0;
}