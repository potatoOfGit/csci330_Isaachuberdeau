#include <iostream>

int main() {
  std::cout << "Enter numeric grade (0-100): ";
  int grade;
  std::cin >> grade;
  char letterGrade;

  // TODO: Validate input
  // TODO: Convert to letter grade using switch
  // TODO: Print result

  if (grade > 100 || grade < 0) {
    std::cout << "Grade must be between 0 and 100!";
    return 1;
  } else if (!(std::cin >> grade)) {
    std::cout << "Invalid input. Please enter a number.\n";
    return 1;
  }

  switch (grade / 10) {
    case (10):
    case (9):
      letterGrade = 'A';
      break;
    case (8):
      letterGrade = 'B';
      break;
    case (7):
      letterGrade = 'C';
      break;
    case (6):
      letterGrade = 'D';
      break;
    default:
      letterGrade = 'F';
  }

  std::cout << "Grade: " << letterGrade;

  return 0;
}