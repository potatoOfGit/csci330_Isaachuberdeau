#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Custom exception classes
class StudentNotFoundException : public std::runtime_error {
 public:
  StudentNotFoundException(const std::string& message)
      : std::runtime_error(message) {}
};

class InvalidGradeException : public std::invalid_argument {
 public:
  InvalidGradeException(const std::string& message)
      : std::invalid_argument(message) {}
};

// Student class
class Student {
 private:
  int id;
  std::string name;
  std::vector<double> grades;

 public:
  Student(int id, const std::string& name) : id(id), name(name) {}

  int get_id() const { return id; }
  const std::string& get_name() const { return name; }
  const std::vector<double>& get_grades() const { return grades; }

  void add_grade(double grade) {
    if (grade < 0 || grade > 100) {
      throw InvalidGradeException("Grade must be between 0 and 100");
    }
    grades.push_back(grade);
  }

  double calculate_gpa() const {
    if (grades.empty()) {
      return 0.0;
    }

    double gpa_sum = 0;
    for (double grade : grades) {
      // Convert percentage grade to 4.0 scale
      double gpa_value;
      if (grade >= 93) {
        gpa_value = 4.0;
      } else if (grade >= 90) {
        gpa_value = 3.7;
      } else if (grade >= 87) {
        gpa_value = 3.3;
      } else if (grade >= 83) {
        gpa_value = 3.0;
      } else if (grade >= 80) {
        gpa_value = 2.7;
      } else if (grade >= 77) {
        gpa_value = 2.3;
      } else if (grade >= 73) {
        gpa_value = 2.0;
      } else if (grade >= 70) {
        gpa_value = 1.7;
      } else if (grade >= 67) {
        gpa_value = 1.3;
      } else if (grade >= 65) {
        gpa_value = 1.0;
      } else {
        gpa_value = 0.0;
      }
      gpa_sum += gpa_value;
    }
    return gpa_sum / grades.size();
  }

  void display() const {
    std::cout << "ID: " << id << ", Name: " << name;
    std::cout << ", GPA: ";

    if (grades.empty()) {
      std::cout << "N/A (no grades)";
    } else {
      std::cout << calculate_gpa();
    }

    std::cout << ", Grades: [";
    for (size_t i = 0; i < grades.size(); i++) {
      std::cout << grades[i];
      if (i < grades.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
  }
};

// RAII File Manager
class StudentFileManager {
 private:
  std::string filename;

 public:
  StudentFileManager(const std::string& filename) : filename(filename) {}

  void save_students(const std::vector<Student>& students) {
    std::ofstream file(filename);

    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    for (const auto& student : students) {
      file << student.get_id() << "|" << student.get_name() << "|";

      const auto& grades = student.get_grades();
      for (size_t i = 0; i < grades.size(); i++) {
        file << grades[i];
        if (i < grades.size() - 1) file << ",";
      }
      file << std::endl;
    }

    // File automatically closed by destructor (RAII)
  }

  std::vector<Student> load_students() {
    std::ifstream file(filename);

    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file for reading: " + filename);
    }

    std::vector<Student> students;
    std::string line;

    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string id_str, name, grades_str;

      if (std::getline(ss, id_str, '|') && std::getline(ss, name, '|') &&
          std::getline(ss, grades_str)) {
        int id = std::stoi(id_str);
        Student student(id, name);

        if (!grades_str.empty()) {
          std::stringstream grade_ss(grades_str);
          std::string grade_str;

          while (std::getline(grade_ss, grade_str, ',')) {
            student.add_grade(std::stod(grade_str));
          }
        }

        students.push_back(student);
      }
    }

    // File automatically closed by destructor (RAII)
    return students;
  }
};

// Main application class
class StudentManagementSystem {
 private:
  std::vector<Student> students;
  StudentFileManager file_manager;

 public:
  StudentManagementSystem(const std::string& data_file)
      : file_manager(data_file) {
    try {
      students = file_manager.load_students();
      std::cout << "Loaded " << students.size() << " students from file."
                << std::endl;
    } catch (const std::exception& e) {
      std::cout << "Warning: Could not load existing data: " << e.what()
                << std::endl;
      std::cout << "Starting with empty database." << std::endl;
    }
  }

  ~StudentManagementSystem() {
    try {
      file_manager.save_students(students);
      std::cout << "Data saved successfully." << std::endl;
    } catch (const std::exception& e) {
      std::cout << "Warning: Could not save data: " << e.what() << std::endl;
    }
  }

  void run() {
    int choice;

    do {
      display_menu();
      std::cout << "Enter choice: ";

      if (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }

      try {
        switch (choice) {
          case 1:
            add_student();
            break;
          case 2:
            remove_student();
            break;
          case 3:
            search_student();
            break;
          case 4:
            display_all_students();
            break;
          case 5:
            add_grade_to_student();
            break;
          case 0:
            std::cout << "Goodbye!" << std::endl;
            break;
          default:
            std::cout << "Invalid choice!" << std::endl;
        }
      } catch (const StudentNotFoundException& e) {
        std::cout << "Student Error: " << e.what() << std::endl;
      } catch (const InvalidGradeException& e) {
        std::cout << "Grade Error: " << e.what() << std::endl;
      } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
      }

    } while (choice != 0);
  }

 private:
  void display_menu() {
    std::cout << "\n=== Student Management System ===" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Remove Student" << std::endl;
    std::cout << "3. Search Student" << std::endl;
    std::cout << "4. Display All Students" << std::endl;
    std::cout << "5. Add Grade to Student" << std::endl;
    std::cout << "0. Exit" << std::endl;
  }

  void add_student() {
    int id;
    std::string name;

    std::cout << "Enter student ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter student name: ";
    std::getline(std::cin, name);

    // Check if ID already exists
    for (const auto& student : students) {
      if (student.get_id() == id) {
        std::cout << "Student with ID " << id << " already exists!"
                  << std::endl;
        return;
      }
    }

    students.push_back(Student(id, name));
    std::cout << "Student added successfully!" << std::endl;
  }

  void remove_student() {
    int id;
    std::cout << "Enter student ID to remove: ";
    std::cin >> id;

    auto it = std::find_if(students.begin(), students.end(),
                           [id](const Student& s) { return s.get_id() == id; });

    if (it != students.end()) {
      std::cout << "Removing student: " << it->get_name() << std::endl;
      students.erase(it);
      std::cout << "Student removed successfully!" << std::endl;
    } else {
      throw StudentNotFoundException("Student with ID " + std::to_string(id) +
                                     " not found");
    }
  }

  void search_student() {
    int id;
    std::cout << "Enter student ID to search: ";
    std::cin >> id;

    Student* student = find_student_by_id(id);
    if (student) {
      std::cout << "\nStudent found:" << std::endl;
      student->display();
    } else {
      throw StudentNotFoundException("Student with ID " + std::to_string(id) +
                                     " not found");
    }
  }

  void display_all_students() {
    if (students.empty()) {
      std::cout << "No students in the system." << std::endl;
      return;
    }

    std::cout << "\n=== All Students ===" << std::endl;
    for (const auto& student : students) {
      student.display();
    }
  }

  void add_grade_to_student() {
    int id;
    double grade;

    std::cout << "Enter student ID: ";
    std::cin >> id;

    Student* student = find_student_by_id(id);
    if (!student) {
      throw StudentNotFoundException("Student with ID " + std::to_string(id) +
                                     " not found");
    }

    std::cout << "Enter grade (0-100): ";
    std::cin >> grade;

    student->add_grade(grade);
    std::cout << "Grade added successfully!" << std::endl;
    std::cout << "New GPA: " << student->calculate_gpa() << std::endl;
  }

  Student* find_student_by_id(int id) {
    for (auto& student : students) {
      if (student.get_id() == id) {
        return &student;
      }
    }
    return nullptr;
  }
};

int main() {
  try {
    StudentManagementSystem system("students.txt");
    system.run();
  } catch (const std::exception& e) {
    std::cout << "Fatal error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}