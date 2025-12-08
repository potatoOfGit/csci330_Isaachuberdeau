#include <iostream>
#include <string>
#include <vector>

void old_style_examples() {
  std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};

  // Old style 1: Index-based
  std::cout << "Old Grades: ";
  for (size_t i = 0; i < grades.size(); ++i) {
    std::cout << grades[i] << " ";
  }
  std::cout << "\n";

  // Old style 2: Iterator-based
  double total = 0.0;
  for (auto it = grades.begin(); it != grades.end(); ++it) {
    total += *it;
  }
  std::cout << "Old Average: " << total / grades.size() << "\n";
}

void modern_style_examples() {
  std::vector<double> grades{85.5, 92.0, 78.5, 96.0, 88.5};

  std::cout << "Modern Grades: ";
  for (const auto& grade : grades) {
    std::cout << grade << " ";
  }
  std::cout << "\n";

  double total = 0.0;
  for (const auto& grade : grades) {
    total += grade;
  }

  std::cout << "Modern Average: " << total / grades.size() << "\n";
}

int main() {
  // TODO: Rewrite the above function using range-based for loops
  // Name your new function: modern_style_examples()

  old_style_examples();
  modern_style_examples();  // Uncomment when ready

  return 0;
}