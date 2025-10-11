#include <iostream>
using namespace std;

template <typename T1, typename T2>
auto swap_values(T1& firstValue, T2& secondValue) {
  T1 storedValue = firstValue;
  firstValue = secondValue;
  secondValue = storedValue;
}

int main() {
  int num1 = 5;
  int num2 = 7;
  double num3 = 0;
  double num4 = 1;

  cout << "Num 1: " << num1 << endl;
  swap_values<int>(num1, num2);
  cout << "Num 1: " << num1 << endl;
  swap_values(num1, num3);
  cout << "Num 1: " << num1 << endl;
}