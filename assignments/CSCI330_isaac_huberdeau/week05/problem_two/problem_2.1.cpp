#include <cmath>
#include <iostream>

struct Shape {
  virtual ~Shape() = default;
  // Add your pure virtual functions here
  virtual double area() const = 0;
  virtual double perimeter() const = 0;

  // This can be implemented in base class
  virtual void display_info() const {
    std::cout << "Area: " << area() << ", Perimeter: " << perimeter() << "\n";
  }
};

struct Rectangle : Shape {
  double width, height;

  Rectangle(double w, double h) : width(w), height(h) {}

  // Implement area() and perimeter()
  double area() const override { return width * height; }

  double perimeter() const override { return (2 * width) + (2 * height); }
};

struct Circle : Shape {
  double radius;

  Circle(double r) : radius(r) {}

  // Implement area() and perimeter()
  // Use M_PI for pi (or 3.14159)
  double area() const override { return M_PI * (radius * radius); }

  double perimeter() const override { return 2 * M_PI * radius; }
};

int main() {
  Shape* shapes[3]{new Rectangle(89.27, 200.11), new Circle(5.1),
                   new Rectangle(3, 2)};

  for (int i = 0; i <= 2; i++) {
    shapes[i]->display_info();
  }

  for (int j = 0; j <= 2; j++) {
    delete shapes[j];
  }
  return 0;
}