#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

using StudentRecord = std::tuple<std::string, int, double>;

class StudentManager {
 public:
  static StudentRecord create_student(const std::string& name, int age,
                                      double gpa) {
    return std::make_tuple(name, age, gpa);
  }

  static std::string get_name(const StudentRecord& student) {
    return std::get<0>(student);
  }

  static int get_age(const StudentRecord& student) {
    return std::get<1>(student);
  }

  static double get_gpa(const StudentRecord& student) {
    return std::get<2>(student);
  }

  static std::string format_student(const StudentRecord& student) {
    std::ostringstream oss;
    oss << std::get<0>(student) << " (" << std::get<1>(student)
        << ") - GPA: " << std::fixed << std::setprecision(2)
        << std::get<2>(student);
    return oss.str();
  }
};

int main() {
  auto student = StudentManager::create_student("Alice Johnson", 20, 3.75);
  assert(StudentManager::get_name(student) == "Alice Johnson");
  assert(StudentManager::get_age(student) == 20);
  assert(StudentManager::get_gpa(student) == 3.75);
  assert(StudentManager::format_student(student) ==
         "Alice Johnson (20) - GPA: 3.75");

  std::cout << "All tests passed!" << std::endl;

  return 0;
}