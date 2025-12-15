#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class FuzzyMatcher {
 public:
  int levenshtein_distance(const std::string& s1, const std::string& s2) {
    // TODO: Calculate edit distance between two strings
    // (insertions, deletions, substitutions needed to transform s1 to s2)

    int len1 = s1.length();
    int len2 = s2.length();

    // Create a 2D DP table
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    // Initialize base cases
    for (int i = 0; i <= len1; ++i) {
      dp[i][0] = i;  // Cost of deleting all characters from s1
    }
    for (int j = 0; j <= len2; ++j) {
      dp[0][j] = j;  // Cost of inserting all characters to match s2
    }

    // Fill the DP table
    for (int i = 1; i <= len1; ++i) {
      for (int j = 1; j <= len2; ++j) {
        if (s1[i - 1] == s2[j - 1]) {
          // Characters match, no operation needed
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          // Take minimum of three operations
          dp[i][j] = 1 + std::min({
                             dp[i - 1][j],     // Deletion
                             dp[i][j - 1],     // Insertion
                             dp[i - 1][j - 1]  // Substitution
                         });
        }
      }
    }

    return dp[len1][len2];
  }

  double similarity_ratio(const std::string& s1, const std::string& s2) {
    // TODO: Calculate similarity ratio (0.0 to 1.0)
    // 1.0 = identical, 0.0 = completely different
    // Formula: 1.0 - (edit_distance / max(len1, len2))

    if (s1.empty() && s2.empty()) {
      return 1.0;  // Both empty strings are identical
    }

    int max_len = std::max(s1.length(), s2.length());
    int distance = levenshtein_distance(s1, s2);

    return 1.0 - (static_cast<double>(distance) / max_len);
  }

  std::vector<std::string> find_similar(
      const std::string& query, const std::vector<std::string>& candidates,
      double threshold = 0.6) {
    // TODO: Find all candidates with similarity >= threshold

    std::vector<std::string> results;

    for (const auto& candidate : candidates) {
      double similarity = similarity_ratio(query, candidate);
      if (similarity >= threshold) {
        results.push_back(candidate);
      }
    }

    // Sort by similarity (highest first)
    std::sort(results.begin(), results.end(),
              [this, &query](const std::string& a, const std::string& b) {
                return similarity_ratio(query, a) > similarity_ratio(query, b);
              });

    return results;
  }

  bool contains_pattern(const std::string& text, const std::string& pattern) {
    // TODO: Check if pattern exists allowing for * (any characters) wildcards
    // Example: pattern "he*o" matches "hello", "hero", "helllo"

    return match_pattern(text, pattern, 0, 0);
  }

 private:
  bool match_pattern(const std::string& text, const std::string& pattern,
                     int text_idx, int pattern_idx) {
    // Base cases
    if (pattern_idx == pattern.length()) {
      return text_idx ==
             text.length();  // Pattern exhausted, text should be too
    }

    if (text_idx == text.length()) {
      // Text exhausted, check if remaining pattern is all wildcards
      for (int i = pattern_idx; i < pattern.length(); ++i) {
        if (pattern[i] != '*') return false;
      }
      return true;
    }

    // Check for wildcard
    if (pattern[pattern_idx] == '*') {
      // Try matching 0 or more characters
      // Option 1: Skip wildcard (match 0 characters)
      if (match_pattern(text, pattern, text_idx, pattern_idx + 1)) {
        return true;
      }
      // Option 2: Match one character and keep the wildcard
      return match_pattern(text, pattern, text_idx + 1, pattern_idx);
    } else {
      // Regular character - must match exactly
      if (text[text_idx] == pattern[pattern_idx]) {
        return match_pattern(text, pattern, text_idx + 1, pattern_idx + 1);
      }
      return false;
    }
  }
};

int main() {
  FuzzyMatcher matcher;

  std::cout << "Edit distance between 'kitten' and 'sitting': "
            << matcher.levenshtein_distance("kitten", "sitting") << std::endl;

  std::cout << "Similarity ratio: " << matcher.similarity_ratio("hello", "helo")
            << std::endl;

  std::vector<std::string> words = {"hello", "world", "help",
                                    "hero",  "hell",  "welcome"};
  auto similar = matcher.find_similar("hello", words, 0.6);

  std::cout << "\nWords similar to 'hello':" << std::endl;
  for (const auto& word : similar) {
    std::cout << "  " << word
              << " (similarity: " << matcher.similarity_ratio("hello", word)
              << ")" << std::endl;
  }

  // Test pattern matching
  std::cout << "\nPattern matching:" << std::endl;
  std::cout << "he*o matches hello: "
            << (matcher.contains_pattern("hello", "he*o") ? "Yes" : "No")
            << std::endl;
  std::cout << "he*o matches world: "
            << (matcher.contains_pattern("world", "he*o") ? "Yes" : "No")
            << std::endl;
  std::cout << "h*o matches hero: "
            << (matcher.contains_pattern("hero", "h*o") ? "Yes" : "No")
            << std::endl;
  std::cout << "*el* matches hello: "
            << (matcher.contains_pattern("hello", "*el*") ? "Yes" : "No")
            << std::endl;

  return 0;
}