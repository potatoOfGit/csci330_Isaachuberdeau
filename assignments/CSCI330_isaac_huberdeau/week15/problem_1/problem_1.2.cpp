#include <iostream>
#include <string>

std::string extract_domain(const std::string& email) {
  // TODO: Extract domain from email address
  // Example: "user@example.com" -> "example.com"

  size_t at_pos = email.find('@');
  if (at_pos != std::string::npos) {
    return email.substr(at_pos + 1);
  }
  return "";  // Return empty string if no @ found
}

std::string extract_filename(const std::string& path) {
  // TODO: Extract filename from file path
  // Example: "/home/user/documents/file.txt" -> "file.txt"

  size_t last_slash = path.find_last_of('/');
  if (last_slash != std::string::npos) {
    return path.substr(last_slash + 1);
  }
  return path;  // Return whole path if no / found
}

int main() {
  std::string email = "alice.smith@university.edu";
  std::string path =
      "/home/student/workspace/assignments/CSCI330_isaac_huberdeau/week15/"
      "problem_1/problem_1.2.cpp";

  std::cout << "Domain: " << extract_domain(email) << std::endl;
  std::cout << "Filename: " << extract_filename(path) << std::endl;

  return 0;
}