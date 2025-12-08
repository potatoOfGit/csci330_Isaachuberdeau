#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};

  // Scenario 1: Just reading/printing (most efficient?)
  std::cout << "Names: ";
  for (const auto& name : names) {  // Fill in the blank
    std::cout << name << " ";
  }
  std::cout << "\n";

  // Scenario 2: Modifying each element
  std::cout << "Adding exclamation marks:\n";
  for (auto& name : names) {  // Fill in the blank
    name += "!";
    std::cout << name << "\n";
  }

  // Scenario 3: Expensive copy objects (what if names were large objects?)
  std::cout << "Efficient reading:\n";
  for (const auto& name : names) {  // Fill in the blank
    std::cout << "Hello, " << name << "\n";
  }

  return 0;
}