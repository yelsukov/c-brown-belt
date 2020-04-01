#pragma once

#include <string>
#include <vector>

using namespace std;

/**
 * Base class for all persons
 */
class Person {
public:
    Person(const string &name, const string &profession);

    /**
     * Common method for person's walking
     * @param destination
     */
    virtual void Walk(const string &destination) const;

    /**
     * Common getter for person's name
     * @return string
     */
    virtual string Name() const;

    /**
     * Common getter for person's profession
     * @return string
     */
    virtual string Profession() const;

protected:
    const string _name;
    const string _profession;
};

class Student : public Person {
public:

    Student(const string &name, const string &song);

    /**
     * Student learns something
     */
    void Learn() const;

    /**
     * Student walks to someplace and sings favorite song
     * Overrides base method
     * @param destination
     */
    void Walk(const string &destination) const override;

    /**
     * Student sings favorite song
     */
    void SingSong() const;

protected:
    string _song;
};


class Teacher : public Person {
public:

    Teacher(const string &name, const string &subject);

    /**
     * Teacher teach to some subject
     */
    void Teach() const;

protected:
    const string _subject;
};


class Policeman : public Person {
public:
    explicit Policeman(const string &name);

    /**
     * Policeman checks a person
     * @param p
     */
    void Check(const Person &p) const;
};

/**
 * Person walks to different places
 * @param person
 * @param places
 */
void VisitPlaces(const Person &person, const vector<string> &places);