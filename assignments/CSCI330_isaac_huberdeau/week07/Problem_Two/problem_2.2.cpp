#include <cmath>
#include <iostream>
using namespace std;

class Vector2D {
 private:
  double x, y;

 public:
  Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

  // Getters
  double get_x() const { return x; }
  double get_y() const { return y; }

  // TODO: Implement these operators

  // Vector addition
  Vector2D operator+(const Vector2D& other) const {
    // Your implementation here
    return Vector2D(x + other.x, y + other.y);
  }

  // Vector subtraction
  Vector2D operator-(const Vector2D& other) const {
    // Your implementation here
    return Vector2D(x + other.x, y + other.y);
  }

  // Scalar multiplication (vector * scalar)
  Vector2D operator*(double scalar) const {
    // Your implementation here
    return Vector2D(x * scalar, y * scalar);
  }

  // Dot product (return scalar)
  double operator*(const Vector2D& other) const {
    // Your implementation here
    return x * other.x + y * other.y;
  }

  // Compound addition
  Vector2D& operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  // Equality (be careful with floating-point comparison!)
  bool operator==(const Vector2D& other) const {
    const double EPSILON = 1e-9;
    return fabs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON;
  }

  // Calculate magnitude
  double magnitude() const { return sqrt(x * x + y * y); }

  // Normalize vector (make it unit length)
  Vector2D normalize() const {
    double mag = magnitude();
    if (mag == 0.0) return Vector2D(0, 0);
    return Vector2D(x / mag, y / mag);
  }
};

// TODO: Implement this non-member function
// Scalar multiplication (scalar * vector)
Vector2D operator*(double scalar, const Vector2D& vec) {
  // Your implementation here
  return vec * scalar;
}

// TODO: Implement stream output operator
ostream& operator<<(ostream& os, const Vector2D& vec) {
  // Format: (x, y)
  // Your implementation here
  os << "(" << vec.get_x() << ", " << vec.get_y() << ")";
  return os;
}

int main() {
  Vector2D v1(3.0, 4.0);
  Vector2D v2(1.0, 2.0);

  cout << "v1: " << v1 << endl;
  cout << "v2: " << v2 << endl;

  Vector2D sum = v1 + v2;
  cout << "v1 + v2: " << sum << endl;

  Vector2D scaled = v1 * 2.0;
  cout << "v1 * 2: " << scaled << endl;

  Vector2D scaled2 = 3.0 * v2;
  cout << "3 * v2: " << scaled2 << endl;

  double dot = v1 * v2;  // dot product
  cout << "v1 · v2: " << dot << endl;

  cout << "Magnitude of v1: " << v1.magnitude() << endl;
  cout << "v1 normalized: " << v1.normalize() << endl;

  return 0;
}