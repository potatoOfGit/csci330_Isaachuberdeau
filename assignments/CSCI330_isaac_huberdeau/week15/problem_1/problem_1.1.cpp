#include <algorithm>
#include <iostream>
#include <string>

int main() {
  // TODO: Complete these string operations

  // 1. Create a string with your name
  std::string name = "Isaac Huberdeau";

  // 2. Create a greeting by concatenating "Hello, " with your name
  std::string greeting = "Hello, " + name;

  // 3. Add an exclamation mark at the end
  greeting += "!";

  // 4. Print the length of the greeting
  std::cout << "Length: " << greeting.length() << std::endl;

  // 5. Print the first and last characters
  std::cout << "First: " << greeting[0] << std::endl;
  std::cout << "Last: " << greeting[greeting.length() - 1] << std::endl;

  // 6. Convert to uppercase (you'll need to look this up!)
  std::transform(greeting.begin(), greeting.end(), greeting.begin(), ::toupper);
  std::cout << "Uppercase: " << greeting << std::endl;

  return 0;
}