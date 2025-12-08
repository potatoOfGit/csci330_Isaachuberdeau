#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  std::vector<std::string> languages{"Python", "Java", "C++", "JavaScript"};

  // Version 1: Traditional index-based approach (like Java)
  std::cout << "Index-based:\n";
  // TODO: Print all elements using indices
  for (int i = 0; i < languages.size(); i++) {
    cout << languages[i] << endl;
  }
  // Version 2: Iterator-based approach
  std::cout << "\nIterator-based:\n";
  // TODO: Print all elements using iterators
  for (auto language = languages.begin(); language != languages.end();
       ++language) {
    cout << *language << endl;
  }

  // Version 3: Range-based for loop (like Python)
  std::cout << "\nRange-based:\n";
  // TODO: Print all elements using range-based for
  for (const auto& langauge : languages) {
    cout << langauge << endl;
  }

  return 0;
}