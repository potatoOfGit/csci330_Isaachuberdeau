#include <cassert>
#include <iostream>
#include <optional>
#include <string>
using namespace std;

class SafeStringProcessor {
 public:
  // Returns the character at index, or nullopt if index is invalid
  static std::optional<char> char_at(const std::string& str, size_t index) {
    if (index > str.length()) {
      return std::nullopt;
    }

    return str[index];
  }

  // Finds the first occurrence of a character, returns its index or nullopt
  static std::optional<size_t> find_char(const std::string& str, char c) {
    size_t pos = str.find(c);
    if (pos == std::string::npos) {
      return std::nullopt;
    }

    return pos;
  }

  // Converts string to integer, returns nullopt if conversion fails
  static std::optional<int> to_int(const std::string& str) {
    try {
      size_t pos;
      int result = std::stoi(str, &pos);
      if (pos != str.length()) {
        return std::nullopt;
      }
      return result;
    } catch (...) {
      return std::nullopt;
    }
  }
};

int main() {
  // Should work
  assert(SafeStringProcessor::char_at("hello", 1) == 'e');
  assert(SafeStringProcessor::find_char("hello", 'l') == 2);
  assert(SafeStringProcessor::to_int("123") == 123);

  // Should return nullopt
  assert(!SafeStringProcessor::char_at("hello", 10).has_value());
  assert(!SafeStringProcessor::find_char("hello", 'x').has_value());
  assert(!SafeStringProcessor::to_int("not_a_number").has_value());

  std::cout << "All tests passed!" << endl;

  return 0;
}