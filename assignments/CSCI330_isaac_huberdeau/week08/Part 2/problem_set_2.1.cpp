#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

double safe_divide(double numerator, double denominator) {
  if (denominator == 0) {
    throw invalid_argument("Division by zero is not allowed");
  }
  return numerator / denominator;
}

int main() {
  double a, b;
  char operation;

  while (true) {
    cout << "Enter calculation (a op b) or 'q' to quit: ";

    if (!(cin >> a >> operation >> b)) {
      if (cin.eof()) break;

      // Handle invalid input
      cout
          << "Invalid input. Please enter numbers and an operator (+, -, *, /)."
          << endl;
      cin.clear();                                          // Clear error flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
      continue;
    }

    try {
      double result;

      // Perform calculation based on operation
      switch (operation) {
        case '+':
          result = a + b;
          break;
        case '-':
          result = a - b;
          break;
        case '*':
          result = a * b;
          break;
        case '/':
          result = safe_divide(a, b);
          break;
        default:
          throw invalid_argument("Invalid operator. Use +, -, *, or /");
      }

      cout << "Result: " << result << endl;

    } catch (const invalid_argument& e) {
      cout << "Error: " << e.what() << endl;
    } catch (const exception& e) {
      cout << "Unexpected error: " << e.what() << endl;
    }
  }

  cout << "Calculator closed." << endl;
  return 0;
}