#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Pair {
 private:
  T first_value;
  T second_value;

 public:
  // Implement constructor and methods here
  Pair(T first_value, T second_value) {
    this->first_value = first_value;
    this->second_value = second_value;
  }

  void swap_values() {
    T stored_num = first();
    set_first(second());
    set_second(stored_num);
  }

  T first() { return first_value; }

  void set_first(T newValue) { first_value = newValue; }

  T second() { return second_value; }

  void set_second(T newValue) { second_value = newValue; }
};

int main() {
  Pair<int> numbers(10, 20);
  cout << "First: " << numbers.first() << ", Second: " << numbers.second()
       << endl;

  numbers.swap_values();
  cout << "After swap - First: " << numbers.first()
       << ", Second: " << numbers.second() << endl;

  Pair<string> words("hello", "world");
  cout << words.first() << " " << words.second() << endl;

  return 0;
}