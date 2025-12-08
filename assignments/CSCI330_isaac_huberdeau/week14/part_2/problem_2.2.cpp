#include <iostream>
#include <string>
#include <vector>

int main() {
  // Task 1: Double all numbers
  std::vector<int> numbers{1, 2, 3, 4, 5};
  for (auto& num : numbers) {
    num *= 2;
  }

  // Task 2: Convert strings to uppercase (first character only)
  std::vector<std::string> words{"hello", "world", "cpp", "iterators"};
  for (auto& word : words) {
    if (!word.empty()) {
      word[0] = toupper(word[0]);
    }
  }

  // Task 3: Count positive numbers
  std::vector<int> mixed{-5, 3, -1, 8, 0, -2, 7};
  int positive_count = 0;
  for (const auto& num : mixed) {
    if (num > 0) {
      positive_count++;
    }
  }

  // Print results to verify
  std::cout << "Doubled numbers: ";
  for (const auto& num : numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  std::cout << "Capitalized words: ";
  for (const auto& word : words) {
    std::cout << word << " ";
  }
  std::cout << "\n";

  std::cout << "Positive count: " << positive_count << "\n";

  return 0;
}