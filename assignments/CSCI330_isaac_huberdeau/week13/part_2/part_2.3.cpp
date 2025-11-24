#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class StudentDatabase {
 private:
  map<int, string> idToName;
  map<string, double> nameToGPA;
  set<string> honorRoll;

 public:
  void addStudent(int id, const string& name, double gpa) {
    idToName[id] = name;
    nameToGPA[name] = gpa;

    if (gpa >= 3.5) {
      honorRoll.insert(name);
    } else {
      honorRoll.erase(name);
    }

    cout << "Added: " << name << " (ID: " << id << ", GPA: " << gpa << ")"
         << endl;
  }

  double findGPAByID(int id) {
    auto it = idToName.find(id);
    if (it != idToName.end()) {
      string name = it->second;
      return nameToGPA[name];
    }
    return -1.0;
  }

  void listHonorRoll() {
    cout << "\n=== Honor Roll Students (GPA >= 3.5) ===" << endl;
    if (honorRoll.empty()) {
      cout << "No students on honor roll." << endl;
      return;
    }

    for (const string& name : honorRoll) {
      cout << name << " - GPA: " << fixed << setprecision(2) << nameToGPA[name]
           << endl;
    }
  }

  void displayAllStudents() {
    cout << "\n=== All Students ===" << endl;
    for (const auto& pair : idToName) {
      int id = pair.first;
      string name = pair.second;
      double gpa = nameToGPA[name];

      cout << "ID: " << id << " | Name: " << name << " | GPA: " << fixed
           << setprecision(2) << gpa << endl;
    }
  }
};

int main() {
  StudentDatabase db;

  db.addStudent(101, "Alice Johnson", 3.8);
  db.addStudent(102, "Bob Smith", 3.2);
  db.addStudent(103, "Charlie Brown", 3.9);
  db.addStudent(104, "Diana Prince", 3.4);
  db.addStudent(105, "Eve Davis", 3.7);

  db.displayAllStudents();

  cout << "\nGPA for student ID 103: " << db.findGPAByID(103) << endl;
  cout << "GPA for student ID 999: " << db.findGPAByID(999) << endl;

  db.listHonorRoll();

  return 0;
}