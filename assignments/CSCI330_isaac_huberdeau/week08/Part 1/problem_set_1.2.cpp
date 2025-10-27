#include <iostream>
using namespace std;

int main() {
  int size;
  char mode;

  std::cout << "Enter pattern size (1-10): ";
  std::cin >> size;

  std::cout << "Show all rows (a) or odd rows only (o)? ";
  std::cin >> mode;

  // TODO: Validate inputs
  // TODO: Generate pattern with nested loops
  // TODO: Use continue for odd-only mode

  if (size < 1 || size > 10) {
    std::cout << "Input must be between 1 and 10.";
    return 1;
  }

  if (mode == 'a') {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < i + 1; j++) {
        std::cout << j + 1;
      }
      std::cout << endl;
    }
  } else if (mode == 'o') {
    for (int i = 0; i < size; i++) {
      if ((i + 1) % 2 == 0) {
        continue;
      } else {
        for (int j = 1; j < i + 2; j++) {
          std::cout << j;
        }
        std::cout << endl;
      }
    }
  } else {
    std::cout << "Not a mode.";
    return 1;
  }

  return 0;
}