#include <iostream>
#include <string>
using namespace std;

int main() {
  // Rewrite these using compound assignment operators
  int score = 100;
  score += 50;
  score *= 2;
  score -= 25;
  score /= 3;
  score %= 10;

  string message = "Hello";
  message += " ";
  message += "World";
  message += "!";

  bool flags = true;
  flags &= false;
  flags |= true;

  cout << "Final score: " << score << endl;
  cout << "Final message: " << message << endl;
  cout << "Final flags: " << flags << endl;

  return 0;
}