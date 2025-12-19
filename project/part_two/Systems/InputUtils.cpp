#include "InputUtils.h"

#include <iostream>
#include <limits>

using namespace std;

int getChoice(int min, int max) {
  int choice;
  while (true) {
    cout << "Enter your choice: ";
    if (cin >> choice && choice >= min && choice <= max) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return choice;
    } else {
      cout << "Invalid choice! Try again.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void waitForEnter() {
  cout << "\nPress Enter to continue...";
  cin.get();
}

void clearInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}