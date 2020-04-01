#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
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

bool IsPalindrom(string s) {
    uint size = s.size();
    if (size <= 1) return true;
    for (size_t i = 1; i < size / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}


void TestCommonCases() {
    Assert(!IsPalindrom("string"), "input string");
    Assert(IsPalindrom("argentinamanitnegra"), "input argentinamanitnegra");
    Assert(IsPalindrom("ss"), "input ss");
    Assert(IsPalindrom("xox"), "input xox");
    Assert(IsPalindrom("madam"), "input madam");
    Assert(IsPalindrom("zzzz"), "input zzzz");
    Assert(!IsPalindrom("strezrts"), "input strezrts");
    Assert(IsPalindrom("wasitacaroracatisaw"), "input wasitacaroracatisaw");
    Assert(!IsPalindrom("asisaw"), "input asisaw");
    Assert(!IsPalindrom("wasisa"), "input wasisa");
    Assert(IsPalindrom("zob boz"), "input zob boz");
}

void TestViolationCases() {
    Assert(IsPalindrom(""), "input empty");
    Assert(IsPalindrom("  "), "input two spaces");
    Assert(IsPalindrom(" ss "), "input  ss ");
    Assert(IsPalindrom("s s"), "input s s");
    Assert(IsPalindrom("s"), "input s");
    Assert(!IsPalindrom("madam\n"), "input with endl");
    Assert(!IsPalindrom("\taba "), "input with tab an space");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestCommonCases, "TestAllCases");
    runner.RunTest(TestViolationCases, "TestViolationCases");

    return 0;
}
