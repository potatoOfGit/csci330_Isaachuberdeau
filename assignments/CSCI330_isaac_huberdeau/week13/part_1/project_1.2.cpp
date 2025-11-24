#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StudentList {
 private:
  vector<string> students;

 public:
  void addStudent(const string& name) { students.push_back(name); }

  void insertStudent(const string& name, int position) {
    if (position >= 0 && position <= students.size()) {
      students.insert(students.begin() + position, name);
    } else {
      cout << "Invalid position!" << endl;
    }
  }

  void removeStudent(const string& name) {
    auto it = find(students.begin(), students.end(), name);
    if (it != students.end()) {
      students.erase(it);
      cout << name << " removed." << endl;
    } else {
      cout << name << " not found." << endl;
    }
  }

  void displayStudents() {
    cout << "\nStudent List:" << endl;
    for (int i = 0; i < students.size(); i++) {
      cout << "Position " << i << ": " << students[i] << endl;
    }
  }
};

int main() {
  StudentList list;

  list.addStudent("Alice");
  list.addStudent("Bob");
  list.addStudent("Charlie");
  list.displayStudents();

  list.insertStudent("David", 1);
  list.displayStudents();

  list.removeStudent("Bob");
  list.displayStudents();

  return 0;
}