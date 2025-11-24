#include <iostream>
#include <vector>

using namespace std;

class Grades {
 private:
  std::vector<double> grades;

 public:
  void append(double grade) { grades.push_back(grade); }

  double findAverage() {
    double average = 0;
    for (int i = 0; i < grades.size(); i++) {
      average += grades[i];
    }

    return average / grades.size();
  }

  double findHighest() {
    double highest = 0;
    for (int j = 0; j < grades.size(); j++) {
      if (grades.at(j) > highest) {
        highest = grades.at(j);
      }
    }

    return highest;
  }
};

int main() {
  Grades grades;
  grades.append(42);
  grades.append(95);
  grades.append(100);
  grades.append(34);
  grades.append(84);
  grades.append(69);

  double highestGrade = grades.findHighest();
  double averageGrade = grades.findAverage();

  cout << "Highest Grade: " << highestGrade << endl;
  cout << "Average Grade: " << averageGrade << endl;

  return 0;
}