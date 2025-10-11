#include <iostream>
using namespace std;

// Your template function here
template <typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator)
    -> decltype(numerator / denominator) {
  // Implement this
  if (denominator == 0) {
    return 0;
  } else {
    return numerator / denominator;
  }
}

int main() {
  cout << "10 / 2 = " << safe_divide(10, 2) << endl;
  cout << "10.5 / 2 = " << safe_divide(10.5, 2) << endl;
  cout << "10 / 0 = " << safe_divide(10, 0) << " (division by zero)" << endl;
  return 0;
}