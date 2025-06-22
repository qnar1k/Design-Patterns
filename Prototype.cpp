#include <iostream>
using namespace std;

class Shape {
public:
	string id;
	string type;
	Shape() {}
	Shape(const Shape& other) {
		this->id = other.id;
		this->type = other.type;
	}
	virtual Shape* clone() const = 0;
	virtual void draw() const = 0;   

	virtual ~Shape() {}
};

class Circle : public Shape {
	int radius;
public:
	Circle(int r) : radius(r) {
		type = "Circle";
	}
	Circle(const Circle& other) : Shape(other) {
		radius = other.radius;
	}
	Shape* clone() const override {
		return new Circle(*this);
	}
	void draw() const override {
		cout << id << " Drawing Circle with radius: " << radius << endl;
	}
};

class Rectangle : public Shape {
public:
	int width, height;

	Rectangle(int w, int h) : width(w), height(h) {
		type = "Rectangle";
	}

	Rectangle(const Rectangle& other) : Shape(other) {
		width = other.width;
		height = other.height;
	}

	Shape* clone() const override {
		return new Rectangle(*this);
	}

	void draw() const override {
		cout << id << " Drawing Rectangle " << width << "x" << height << endl;
	}
};
int main()
{
	Circle originalCircle(10);
	originalCircle.id = "circle1";

	Rectangle originalRectangle(20, 15);
	originalRectangle.id = "rect1";

	// Clone objects
	Shape* circleClone = originalCircle.clone();
	circleClone->id = "circle2";

	Shape* rectClone = originalRectangle.clone();
	rectClone->id = "rect2";

	// Use objects
	originalCircle.draw();
	circleClone->draw();

	originalRectangle.draw();
	rectClone->draw();

	// Clean up
	delete circleClone;
	delete rectClone;

	return 0;
}

