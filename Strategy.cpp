#include <iostream>
#include <cmath>
#include <memory>
using namespace std;
#define M_PI 3.14 

class TriangleAreaStrategy {
public:
    virtual double calculateArea() const = 0;
    virtual ~TriangleAreaStrategy() = default;
};

class BaseHeightStrategy : public TriangleAreaStrategy {
private:
    double base;
    double height;

public:
    BaseHeightStrategy(double base, double height) : base(base), height(height) {}
    double calculateArea() const override {
        return 0.5 * base * height;
    }
};

class ThreeSidesStrategy : public TriangleAreaStrategy {
private:
    double a, b, c;

public:
    ThreeSidesStrategy(double a, double b, double c) : a(a), b(b), c(c) {}
    double calculateArea() const override {
        double s = (a + b + c) / 2; 
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

class TwoSidesAngleStrategy : public TriangleAreaStrategy {
private:
    double side1;
    double side2;
    double angleInDegrees;

public:
    TwoSidesAngleStrategy(double side1, double side2, double angleInDegrees)
        : side1(side1), side2(side2), angleInDegrees(angleInDegrees) {}
    double calculateArea() const override {
        double angleInRadians = angleInDegrees * M_PI / 180.0;
        return 0.5 * side1 * side2 * sin(angleInRadians);
    }
};

class Triangle {
private:
    unique_ptr<TriangleAreaStrategy> areaStrategy;

public:
    void setAreaStrategy(unique_ptr<TriangleAreaStrategy> strategy) {
        areaStrategy = move(strategy);
    }

    double calculateArea() const {
        if (!areaStrategy) {
            cerr << "Error: No area calculation strategy set.\n";
            return 0;
        }
        return areaStrategy->calculateArea();
    }
};

int main() {
    Triangle triangle;

    triangle.setAreaStrategy(make_unique<BaseHeightStrategy>(10.0, 5.0));
    cout << "Area (Base & Height): " << triangle.calculateArea() << "\n";

    triangle.setAreaStrategy(make_unique<ThreeSidesStrategy>(7.0, 8.0, 9.0));
    cout << "Area (Three Sides): " << triangle.calculateArea() << "\n";

    triangle.setAreaStrategy(make_unique<TwoSidesAngleStrategy>(5.0, 7.0, 45.0));
    cout << "Area (Two Sides & Angle): " << triangle.calculateArea() << "\n";

    return 0;
}
