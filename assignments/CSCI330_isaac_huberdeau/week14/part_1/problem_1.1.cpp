#include <iostream>
#include <vector>
using namespace std;

int main() {
  std::vector<int> numbers{10, 20, 30, 40, 50};

  // TODO: Use iterators to complete these tasks:
  // 1. Print the first element using an iterator
  auto first = numbers.begin();
  cout << "First Element: " << *first << endl;
  // 2. Print the last element using an iterator
  auto last = numbers.end() - 1;
  cout << "Last Element: " << *last << endl;
  // 3. Print all elements using a traditional iterator loop
  for (auto number = numbers.begin(); number != numbers.end(); ++number) {
    cout << *number << endl;
  }

  return 0;
}