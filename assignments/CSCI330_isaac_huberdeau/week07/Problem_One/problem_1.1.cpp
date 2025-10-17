#include <iostream>
using namespace std;

int main() {
  int a = 10, b = 20, c = 5;

  // Question 1: What is the value of result1? 110
  int result1 = a + b * c;
  cout << "result1: " << result1 << endl;

  // Question 2: What is the value of result2? 150
  int result2 = (a + b) * c;
  cout << "result2: " << result2 << endl;

  // Question 3: What is the value of result3? 20
  int result3 = a < b && b > c;
  cout << "result3: " << result3 << endl;

  // Question 4: What is the value of result4? 15
  bool result4 = a < b || b < c && c > a;
  cout << "result4: " << result4 << endl;

  // Question 5: What are the final values of x and y? 7 and 13
  int x = 5;
  int y = ++x + x++;
  cout << "x: " << x << ", y: " << y << endl;

  return 0;
}