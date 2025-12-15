#include <iostream>
#include <sstream>
#include <string>

class StringCompressor {
 public:
  std::string run_length_encode(const std::string& input) {
    // TODO: Implement run-length encoding
    // Example: "aaabbc" -> "a3b2c1"
    // Example: "abcd" -> "a1b1c1d1" (or return original if not shorter)

    if (input.empty()) {
      return input;
    }

    std::ostringstream encoded;
    int count = 1;

    for (size_t i = 0; i < input.length(); ++i) {
      // Check if next character is the same
      if (i + 1 < input.length() && input[i] == input[i + 1]) {
        count++;
      } else {
        // Write character and count
        encoded << input[i] << count;
        count = 1;
      }
    }

    std::string result = encoded.str();

    // Return original if encoded version is not shorter
    return (result.length() < input.length()) ? result : input;
  }

  std::string run_length_decode(const std::string& encoded) {
    // TODO: Decode run-length encoded string
    // Example: "a3b2c1" -> "aaabbc"

    std::ostringstream decoded;

    for (size_t i = 0; i < encoded.length(); ++i) {
      char ch = encoded[i];

      // Next character(s) should be digit(s)
      if (i + 1 < encoded.length() && std::isdigit(encoded[i + 1])) {
        // Extract the count (handle multi-digit numbers)
        std::string count_str;
        size_t j = i + 1;
        while (j < encoded.length() && std::isdigit(encoded[j])) {
          count_str += encoded[j];
          j++;
        }

        int count = std::stoi(count_str);

        // Append character 'count' times
        for (int k = 0; k < count; ++k) {
          decoded << ch;
        }

        // Move index past the digits
        i = j - 1;
      }
    }

    return decoded.str();
  }

  std::string remove_duplicates(const std::string& input) {
    // TODO: Remove consecutive duplicate characters
    // Example: "aaabbbccc" -> "abc"
    // Example: "abccba" -> "abcba"

    if (input.empty()) {
      return input;
    }

    std::string result;
    result += input[0];  // Add first character

    for (size_t i = 1; i < input.length(); ++i) {
      // Only add if different from previous character
      if (input[i] != input[i - 1]) {
        result += input[i];
      }
    }

    return result;
  }
};

int main() {
  StringCompressor compressor;

  std::string test1 = "aaabbbccc";
  std::string test2 = "abcdef";
  std::string test3 = "aabbcc";

  std::cout << "Original: " << test1 << std::endl;
  std::string encoded1 = compressor.run_length_encode(test1);
  std::cout << "Encoded: " << encoded1 << std::endl;
  std::cout << "Decoded: " << compressor.run_length_decode(encoded1)
            << std::endl;

  std::cout << "\nDuplicate removal:" << std::endl;
  std::cout << test1 << " -> " << compressor.remove_duplicates(test1)
            << std::endl;
  std::cout << "abccba -> " << compressor.remove_duplicates("abccba")
            << std::endl;

  std::cout << "\nAdditional tests:" << std::endl;
  std::cout << "Original: " << test2 << std::endl;
  std::string encoded2 = compressor.run_length_encode(test2);
  std::cout << "Encoded: " << encoded2 << " (not shorter, returns original)"
            << std::endl;

  return 0;
}