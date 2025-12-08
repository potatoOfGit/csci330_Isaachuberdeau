#include <iostream>
#include <vector>

int main() {
  std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // BUGGY CODE - Don't run this as-is!
  for (auto it = numbers.begin(); it != numbers.end();) {
    if (*it % 2 == 0) {
      it = numbers.erase(it);  // This invalidates the iterator!
    } else {
      ++it;
    }
  }

  // TODO: Fix the above code to safely remove even numbers
  // Hint: erase() returns an iterator to the next element

  std::cout << "Odd numbers remaining: ";
  for (const auto& num : numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  return 0;
}