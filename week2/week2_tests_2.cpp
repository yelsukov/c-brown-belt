#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

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


void TestAllCases() {
    Person p;

    p.ChangeFirstName(1983, "Vasya");
    AssertEqual(p.GetFullName(1983), "Vasya with unknown last name", "firstname is Vasya && lastname is empty");

    p.ChangeFirstName(1985, "Petr");
    AssertEqual(p.GetFullName(1985), "Petr with unknown last name", "firstname is Petr && lastname is empty");

    p.ChangeLastName(1983, "Petrov");
    AssertEqual(p.GetFullName(1983), "Vasya Petrov", "firstname is Petr && lastname is Petrov for 1983");
    AssertEqual(p.GetFullName(1985), "Petr Petrov", "firstname is Petr && lastname is Petrov for 1985");

    p.ChangeLastName(2005, "Petrova");
    AssertEqual(p.GetFullName(2005), "Petr Petrova", "firstname is Petr && lastname is Petrova");

    p.ChangeFirstName(2005, "");
    AssertEqual(p.GetFullName(2005), "Petrova with unknown first name", "firstname is empty && lastname is Petrova");

    p.ChangeLastName(2006, "");
    AssertEqual(p.GetFullName(2006), "Incognito", "firstname is empty && lastname is empty");

    AssertEqual(p.GetFullName(1982), "Incognito", "Did not born");

    AssertEqual(p.GetFullName(2026), "Incognito", "firstname is empty && lastname is empty for 2026");

    p.ChangeFirstName(2026, "Svetlana");
    p.ChangeLastName(2026, "Ivanova");
    AssertEqual(p.GetFullName(2026), "Svetlana Ivanova", "firstname is Svetlana && lastname is Ivanova for 2026");
    AssertEqual(p.GetFullName(2029), "Svetlana Ivanova", "firstname is Svetlana && lastname is Ivanova for 2029");

}

int main() {
    TestRunner runner;
    runner.RunTest(TestAllCases, "TestAllCases");

    return 0;
}