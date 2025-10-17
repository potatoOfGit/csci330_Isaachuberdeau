#include <cmath>
#include <iostream>
using namespace std;

int main() {
  // Bug 1: Integer division problem
  int total_items = 17;
  int groups = 5;
  double average = static_cast<double>(total_items) /
                   groups;  // Should be 3.4, but gives 3.0
  cout << "Average: " << average << endl;

  // Bug 2: Signed/unsigned comparison
  int signed_value = -1;
  unsigned int unsigned_value = 1;
  if (signed_value < static_cast<int>(unsigned_value)) {
    cout << "This might not print when you expect!" << endl;
  }

  // Bug 3: Loss of precision
  double precise_value = 3.99999;
  int truncated = std::round(precise_value);  // We want to round, not truncate
  cout << "Rounded value should be 4, got: " << truncated << endl;

  return 0;
}