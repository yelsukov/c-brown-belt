#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    istringstream is(s);
    while(!is.eof()) {
        string word;
        getline(is, word, ' ');
        result.push_back(word);
    }

    return result;
}
