#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class TextAnalyzer {
 private:
  std::string text;

 public:
  TextAnalyzer(const std::string& input) : text(input) {}

  int count_words() {
    // TODO: Count words (separated by whitespace)
    int count = 0;
    bool in_word = false;

    for (char c : text) {
      if (std::isspace(c)) {
        in_word = false;
      } else {
        if (!in_word) {
          count++;
          in_word = true;
        }
      }
    }

    return count;
  }

  int count_sentences() {
    // TODO: Count sentences (ending with . ! ?)
    int count = 0;

    for (char c : text) {
      if (c == '.' || c == '!' || c == '?') {
        count++;
      }
    }

    return count;
  }

  std::map<char, int> character_frequency() {
    // TODO: Count frequency of each alphabetic character (case-insensitive)
    std::map<char, int> freq;

    for (char c : text) {
      if (std::isalpha(c)) {
        char lower = std::tolower(c);
        freq[lower]++;
      }
    }

    return freq;
  }

  std::string most_common_word() {
    // TODO: Find the most frequently occurring word (case-insensitive)
    std::map<std::string, int> word_count;
    std::string current_word;

    // Extract and count words
    for (char c : text) {
      if (std::isalpha(c)) {
        current_word += std::tolower(c);
      } else {
        if (!current_word.empty()) {
          word_count[current_word]++;
          current_word.clear();
        }
      }
    }

    // Don't forget the last word if text doesn't end with punctuation
    if (!current_word.empty()) {
      word_count[current_word]++;
    }

    // Find the most common word
    std::string most_common;
    int max_count = 0;

    for (const auto& pair : word_count) {
      if (pair.second > max_count) {
        max_count = pair.second;
        most_common = pair.first;
      }
    }

    return most_common;
  }

  void print_statistics() {
    std::cout << "Words: " << count_words() << std::endl;
    std::cout << "Sentences: " << count_sentences() << std::endl;
    std::cout << "Most common word: " << most_common_word() << std::endl;

    std::cout << "Character frequencies:" << std::endl;
    auto freq = character_frequency();
    for (const auto& pair : freq) {
      std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
  }
};

int main() {
  std::string text =
      "The quick brown fox jumps over the lazy dog. "
      "The dog was sleeping in the sun. What a beautiful day!";

  TextAnalyzer analyzer(text);
  analyzer.print_statistics();

  return 0;
}