#include <cctype>
#include <iostream>
#include <string>

bool is_valid_password(const std::string& password) {
  // TODO: Validate password with these rules:
  // - At least 8 characters long
  // - Contains at least one uppercase letter
  // - Contains at least one lowercase letter
  // - Contains at least one digit

  if (password.length() < 8) {
    return false;
  }

  bool has_upper = false;
  bool has_lower = false;
  bool has_digit = false;

  for (char c : password) {
    if (std::isupper(c)) has_upper = true;
    if (std::islower(c)) has_lower = true;
    if (std::isdigit(c)) has_digit = true;
  }

  return has_upper && has_lower && has_digit;
}

bool is_palindrome(const std::string& text) {
  // TODO: Check if text is a palindrome (reads same forwards/backwards)
  // Ignore case and spaces
  // Example: "A man a plan a canal Panama" -> true

  std::string cleaned;

  // Remove spaces and convert to lowercase
  for (char c : text) {
    if (!std::isspace(c)) {
      cleaned += std::tolower(c);
    }
  }

  // Check if palindrome by comparing characters from both ends
  int left = 0;
  int right = cleaned.length() - 1;

  while (left < right) {
    if (cleaned[left] != cleaned[right]) {
      return false;
    }
    left++;
    right--;
  }

  return true;
}

int main() {
  // Test passwords
  std::cout << "Password1: "
            << (is_valid_password("Password1") ? "Valid" : "Invalid")
            << std::endl;
  std::cout << "weak: " << (is_valid_password("weak") ? "Valid" : "Invalid")
            << std::endl;

  // Test palindromes
  std::cout << "racecar: "
            << (is_palindrome("racecar") ? "Palindrome" : "Not palindrome")
            << std::endl;
  std::cout << "hello: "
            << (is_palindrome("hello") ? "Palindrome" : "Not palindrome")
            << std::endl;

  return 0;
}