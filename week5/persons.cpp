#include <iostream>

#include "persons.h"

using namespace std;

/**
 * Person implementation
 */
Person::Person(const string &name, const string &profession) : _name(name), _profession(profession) {}

void Person::Walk(const string &destination) const {
    cout << this->_profession << ": " << this->_name << " walks to: " << destination << endl;
}

string Person::Name() const {
    return this->_name;
}

string Person::Profession() const {
    return this->_profession;
}

/**
 * Student implementation
 */
Student::Student(const string &name, const string &song) : Person(name, "Student"), _song(song) {}

void Student::Learn() const {
    cout << "Student: " << this->_name << " learns" << endl;
}

void Student::Walk(const string &destination) const {
    Person::Walk(destination);
    this->SingSong();
}

void Student::SingSong() const {
    cout << "Student: " << this->_name << " sings a song: " << this->_song << endl;
}

/**
 * Teacher implementation
 */
Teacher::Teacher(const string &name, const string &subject) : Person(name, "Teacher"), _subject(subject) {}

void Teacher::Teach() const {
    cout << "Teacher: " << this->_name << " teaches: " << this->_subject << endl;
}

/**
 * Policeman implementation
 */
Policeman::Policeman(const string &name) : Person(name, "Policeman") {}

void Policeman::Check(const Person &p) const {
    cout << "Policeman: " << this->_name << " checks " << p.Profession() << ". "
         << p.Profession() << "'s name is: " << p.Name() << endl;
}


void VisitPlaces(const Person &person, const vector<string> &places) {
    for (auto &p : places) {
        person.Walk(p);
    }
}