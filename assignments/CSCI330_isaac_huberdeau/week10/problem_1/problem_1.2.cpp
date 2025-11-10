#include <iostream>
#include <memory>
#include <string>

class Shape {
 public:
  virtual ~Shape() = default;
  virtual void draw() const = 0;
  virtual double area() const = 0;
};

class Circle : public Shape {
  double radius;

 public:
  Circle(double r) : radius(r) {}
  void draw() const override {
    std::cout << "Drawing circle with radius " << radius << std::endl;
  }
  double area() const override { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape {
  double width, height;

 public:
  Rectangle(double w, double h) : width(w), height(h) {}
  void draw() const override {
    std::cout << "Drawing rectangle " << width << "x" << height << std::endl;
  }
  double area() const override { return width * height; }
};

class ShapeFactory {
 public:
  // TODO: Implement this method
  static std::unique_ptr<Shape> create_shape(const std::string& type,
                                             double param1, double param2 = 0) {
    if (type == "circle") {
      return std::make_unique<Circle>(param1);
    } else if (type == "rectangle") {
      return std::make_unique<Rectangle>(param1, param2);
    }
    return nullptr;
  }
};

int main() {
  auto circle = ShapeFactory::create_shape("circle", 5.0);
  auto rectangle = ShapeFactory::create_shape("rectangle", 3.0, 4.0);
  auto unknown = ShapeFactory::create_shape("triangle", 1.0, 2.0);

  if (circle) {
    circle->draw();
    std::cout << "Area: " << circle->area() << std::endl;
  }

  if (rectangle) {
    rectangle->draw();
    std::cout << "Area: " << rectangle->area() << std::endl;
  }

  if (!unknown) {
    std::cout << "Unknown shape type" << std::endl;
  }

  return 0;
}