#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Figure {
public:
    Figure(const string &new_name)
            : name(new_name) {}

    virtual double Perimeter() const = 0;

    virtual double Area() const = 0;

    virtual string Name() {
        return this->name;
    }

protected:
    const string name = "base";
};

class Rect : public Figure {
public:
    Rect(const uint16_t &new_width, const uint16_t &new_height)
            : Figure("RECT"), width(new_width), height(new_height) {};

    double Perimeter() const override {
        return (this->height + this->width) * 2;
    }

    double Area() const override {
        return this->height * this->width;
    }

protected:
    const uint16_t width;
    const uint16_t height;
};

class Triangle : public Figure {
public:
    Triangle(const uint16_t na, const uint16_t nb, const uint16_t nc)
            : Figure("TRIANGLE"), a(na), b(nb), c(nc) {
    };

    double Perimeter() const override {
        return this->a + this->b + this->c;
    }

    double Area() const override {
        double p = this->Perimeter() / 2.0;

        return sqrt(p * (p - this->a) * (p - this->b) * (p - this->c));
    }

protected:
    const uint16_t a;
    const uint16_t b;
    const uint16_t c;
};

class Circle : public Figure {
public:
    Circle(const uint16_t new_radius)
            : Figure("CIRCLE"), radius(new_radius) {};

    double Perimeter() const override {
        return 2 * this->pi * this->radius;
    }

    double Area() const override {
        return this->pi * pow(this->radius, 2);
    }

protected:
    const uint16_t radius;
    const double pi = 3.14;
};

shared_ptr<Figure> CreateFigure(istream &is) {
    string figure;
    is >> figure;

    if (figure == "RECT") {
        uint16_t w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    }

    if (figure == "TRIANGLE") {
        uint16_t a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }

    if (figure == "CIRCLE") {
        uint16_t r;
        is >> r;
        return make_shared<Circle>(r);
    }

    throw invalid_argument("Unknown figure");
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}