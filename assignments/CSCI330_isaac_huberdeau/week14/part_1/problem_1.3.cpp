#include <iostream>
#include <vector>
using namespace std;

int main() {
  std::vector<int> data{1, 3, 5, 7, 9, 11, 13, 15};

  // TODO: Using iterators, accomplish these tasks:
  // 1. Print the element at position 3 (should be 7)
  auto thirdPosition = data.at(3);
  cout << "Third Element: " << thirdPosition << "\n" << endl;
  // 2. Print every other element starting from the beginning
  cout << "Every Other Element:" << endl;
  for (auto everyOther = data.begin(); everyOther != data.end();
       everyOther += 2) {
    cout << *everyOther << endl;
  }
  // 3. Print the last 3 elements
  cout << "\nLast Three elements" << endl;
  for (auto lastThree = data.end() - 3; lastThree != data.end(); ++lastThree) {
    cout << *lastThree << endl;
  }

  return 0;
}