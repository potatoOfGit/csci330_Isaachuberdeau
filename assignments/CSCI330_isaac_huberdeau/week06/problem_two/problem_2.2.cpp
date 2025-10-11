#include <iostream>
#include <string>
using namespace std;

template <typename T>
class SimpleArray {
 private:
  T* data;
  size_t array_size;

 public:
  SimpleArray(size_t size) : array_size(size) { data = new T[size]; }

  ~SimpleArray() { delete[] data; }

  // Implement the rest of the methods
  T get(int index) {
    if (index < array_size && index >= 0) {
      return data[index];
    } else {
      throw out_of_range("Invalid Index!!!");
    }
  }

  void set(int index, T value) { data[index] = value; }

  int size() { return array_size; }
};

int main() {
  SimpleArray<int> numbers(5);
  numbers.set(0, 100);
  numbers.set(1, 200);
  cout << "numbers[0] = " << numbers.get(0) << endl;
  cout << "Size: " << numbers.size() << endl;

  SimpleArray<string> words(3);
  words.set(0, "apple");
  words.set(1, "banana");
  cout << "words[0] = " << words.get(0) << endl;

  return 0;
}