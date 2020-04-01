#include "Person.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintStats(std::vector<Person> persons) {
    auto female_end = partition(persons.begin(), persons.end(), [](const Person &p) {
        return p.gender == Gender::FEMALE;
    });
    auto female_employed_end = partition(persons.begin(), female_end, [](const Person &p) {
        return p.is_employed;
    });
    auto male_employed_end = partition(female_end, persons.end(), [](const Person &p) {
        return p.is_employed;
    });

    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), female_end) << endl;
    cout << "Median age for males = " << ComputeMedianAge(female_end, persons.end()) << endl;
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), female_employed_end) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(female_employed_end, female_end) << endl;
    cout << "Median age for employed males = " << ComputeMedianAge(female_end, male_employed_end) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(male_employed_end, persons.end()) << endl;
}