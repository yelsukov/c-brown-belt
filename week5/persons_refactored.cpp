#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Base class for all persons
 */
class Person {
public:
    /**
     * Constructor for Person
     * @param string name          Name of person
     * @param string profession    Profession of person
     */
    Person(const string &name, const string &profession) : _name(name), _profession(profession) {}

    /**
     * Common method for person's walking
     * @param string destination    Destination of walking
     */
    virtual void Walk(const string &destination) const {
        cout << this->_ActionLabel() << " walks to: " << destination << endl;
    }

    /**
     * Common getter for person's name
     * @return string
     */
    virtual string Name() const {
        return this->_name;
    }

    /**
     * Common getter for person's profession
     * @return string
     */
    virtual string Profession() const {
        return this->_profession;
    }

protected:
    const string _name;
    const string _profession;

    virtual string _ActionLabel() const {
        return this->_profession + ": " + this->_name;
    }
};

/**
 * Student implementation
 */
class Student : public Person {
public:

    /**
     * Constructor for Student
     * @param string name
     * @param string song    Favorite song of student
     */
    Student(const string &name, const string &song) : Person(name, "Student"), _song(song) {}

    /**
     * Student learns something
     */
    void Learn() const {
        cout << this->_ActionLabel() << " learns" << endl;
    }

    /**
     * Student walks to someplace and sings favorite song
     * Overrides base method
     * @param destination
     */
    void Walk(const string &destination) const override {
        Person::Walk(destination);
        this->SingSong();
    }

    /**
     * Student sings favorite song
     */
    void SingSong() const {
        cout << this->_ActionLabel() << " sings a song: " << this->_song << endl;
    }

protected:
    const string _song;
};

/**
 * Teacher implementation
 */
class Teacher : public Person {
public:
    /**
     * Constructor for teacher
     * @param string name
     * @param string subject    The name of the subject that the teacher teaches
     */
    Teacher(const string &name, const string &subject) : Person(name, "Teacher"), _subject(subject) {}

    /**
     * Teacher teach to some subject
     */
    void Teach() const {
        cout << this->_ActionLabel() << " teaches: " << this->_subject << endl;
    }

protected:
    const string _subject;
};

/**
 * Policeman implementation
 */
class Policeman : public Person {
public:
    /**
     * Constructor for Policeman
     * @param string name
     */
    explicit Policeman(const string &name) : Person(name, "Policeman") {}

    /**
     * Policeman checks a person
     * @param Person p    Person to check
     */
    void Check(const Person &p) const {
        cout << this->_ActionLabel() << " checks " << p.Profession() << ". "
             << p.Profession() << "'s name is: " << p.Name() << endl;
    }
};

/**
 * Person walks to different places
 * @param person
 * @param places
 */
void VisitPlaces(const Person &person, const vector<string> &places) {
    for (auto &p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    VisitPlaces(t, {"Moscow", "London"});
    t.Teach();

    Student s("Ann", "We will rock you");
    VisitPlaces(s, {"Party", "Library"});
    s.Learn();

    Policeman p("Bob");
    Policeman p2("Jack");
    VisitPlaces(p, {"Office", "Home"});
    p.Check(s);
    p.Check(p2);
    p.Check(t);

    return 0;
}