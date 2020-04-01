#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public :
    Person(const string& name)
            : name_(name)
    {};

    virtual void Walk(const string& destination) const {
        cout << introduceYourself() <<  " walks to: " << destination << endl;
    }

    virtual string getType() const = 0;
    virtual const string& getName() const {
        return name_;
    }

protected:
    virtual string introduceYourself() const {
        return getType() + " " + getName();
    }

    const string name_;
};

class Student : public Person {
public:
    Student(const string name, const string favouriteSong)
            : Person(name),
              favouriteSong_(favouriteSong)
    {};

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }
    void SingSong() const {
        cout << introduceYourself() << " sings a song: " << favouriteSong_ << endl;
    }
    void Learn() const {
        cout << introduceYourself() << " learns" << endl;
    }
    string getType() const override {
        return "Student";
    }

private:
    const string favouriteSong_;
};

class Teacher :public Person {
public:
    Teacher(const string& name, const string& subject)
            : Person(name),
              subject_(subject)
    {};

    string getType() const override {
        return "Teacher";
    }

    void Teach() const {
        cout << introduceYourself() << " teaches: " << subject_ << endl;
    }

private:
    const string subject_;
};

class Policeman : public Person {
public:
    Policeman(const string& name)
            : Person(name)
    {};
    string getType() const override {
        return "Policeman";
    }

    void Check(const Person& person) {
        cout << introduceYourself() << " checks " << person.getType() << '.' << endl;
        cout << person.getType() << "'s name is: " << person.getName() << endl;
    }
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    cout << endl;
    p.Check(s);
    cout << endl;
    VisitPlaces(s, { "Moscow", "London" });
    cout << endl;
    return 0;
}
