#include <iostream>
using namespace std;

template <typename T>
class Calculator {
 private:
  T value;

 public:
  Calculator(T initial) : value(initial) {}

  void add(T amount) { value += amount; }

  void print() { cout << "Result: " << value << endl; }

  // Bug 1: Missing template syntax in method definition outside class
  T getValue();
};

template <typename T>
T Calculator<T>::getValue() {  // did not declare typename before it, and didn't
                               // have <T> after Calculator. So it didn;t know
                               // it was calling the calculator class.
  return value;
}

// Bug 2: Some types don't have do somehting, so we use an alternative fucntion
// just in case.
template <typename T>
auto processValue(T val) -> decltype(val.doSomething(), void()) {
  val.doSomething();
}

template <typename T>
void processValue(T value) {
  cout << value << endl;
}

int main() {
  Calculator<int> calc(10);
  calc.add(5);
  calc.print();
  cout << "Final value: " << calc.getValue() << endl;

  // Bug 3: This will cause compilation error
  processValue(42);  // int doesn't have doSomething()

  return 0;
}