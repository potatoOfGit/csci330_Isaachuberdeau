#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

struct Student {
  string name;
  int id;
  string major;

  Student(const string& n, int i, const string& m) : name(n), id(i), major(m) {}

  bool operator==(const Student& other) const { return id == other.id; }
};

struct StudentHash {
  size_t operator()(const Student& student) const {
    return hash<int>()(student.id);
  }
};

class StudentRegistry {
 private:
  unordered_set<Student, StudentHash> students;

 public:
  bool addStudent(const Student& student) {
    auto result = students.insert(student);
    if (result.second) {
      cout << "Added: " << student.name << " (ID: " << student.id
           << ", Major: " << student.major << ")" << endl;
      return true;
    } else {
      cout << "Duplicate ID " << student.id << " - Student not added" << endl;
      return false;
    }
  }

  void displayAll() {
    cout << "\n=== All Students ===" << endl;
    for (const auto& student : students) {
      cout << "Name: " << student.name << " | ID: " << student.id
           << " | Major: " << student.major << endl;
    }
  }

  size_t getCount() { return students.size(); }
};

int main() {
  StudentRegistry registry;

  registry.addStudent(Student("Alice Johnson", 101, "Computer Science"));
  registry.addStudent(Student("Bob Smith", 102, "Mathematics"));
  registry.addStudent(Student("Alice Johnson", 103, "Physics"));
  registry.addStudent(Student("Charlie Brown", 101, "Engineering"));
  registry.addStudent(Student("Diana Prince", 104, "Chemistry"));

  registry.displayAll();

  cout << "\nTotal unique students: " << registry.getCount() << endl;

  return 0;
}