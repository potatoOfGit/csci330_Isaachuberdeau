#include <iostream>
#include <string>
using namespace std;

// General template
template <typename T>
class Printer {
 public:
  static void print(const T& value) { cout << "Value: " << value << endl; }
};

template <>
class Printer<bool> {
 public:
  static void print(const bool value) { cout << "Value: " << value << endl; }
};

template <>
class Printer<string> {
 public:
  static void print(const string value) { cout << "Value: " << value << endl; }
};

// TODO: Add specializations for bool and string
// Hint: template<> class Printer<bool> { ... };

int main() {
  Printer<int>::print(42);
  Printer<bool>::print(true);
  Printer<string>::print("hello world");
  Printer<double>::print(3.14);
  return 0;
}