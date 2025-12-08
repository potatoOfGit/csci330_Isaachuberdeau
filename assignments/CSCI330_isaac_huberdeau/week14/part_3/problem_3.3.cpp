#include <iostream>
#include <string>
#include <vector>

struct Student {
  std::string name;
  std::vector<double> grades;

  // TODO: Add a method to calculate average grade using iterators
  double calculate_average() const {
    if (grades.empty()) return 0.0;
    // Use iterators to sum grades and return average
    double total = 0.0;
    for (auto grade = grades.begin(); grade != grades.end(); ++grade) {
      total += *grade;
    }
    return total / grades.size();
  }
};

int main() {
  std::vector<Student> class_roster{{"Alice", {85.0, 92.0, 78.0, 95.0}},
                                    {"Bob", {88.0, 76.0, 92.0, 85.0}},
                                    {"Charlie", {92.0, 88.0, 95.0, 90.0}}};

  // TODO: Using iterators and/or range-based for loops:
  // 1. Print each student's name and average grade
  std::cout << "Student Averages:\n";
  for (const auto& student : class_roster) {
    std::cout << student.name << ": " << student.calculate_average() << "\n";
  }
  // 2. Find the student with the highest average
  auto highest = class_roster.begin();
  for (auto it = class_roster.begin(); it != class_roster.end(); ++it) {
    if (it->calculate_average() > highest->calculate_average()) {
      highest = it;
    }
  }
  std::cout << "\nHighest average: " << highest->name << " ("
            << highest->calculate_average() << ")\n";
  // 3. Count how many students have an average above 85.0
  int count = 0;
  for (const auto& student : class_roster) {
    if (student.calculate_average() > 85.0) {
      count++;
    }
  }
  std::cout << "\nStudents with average > 85.0: " << count << "\n";

  return 0;
}