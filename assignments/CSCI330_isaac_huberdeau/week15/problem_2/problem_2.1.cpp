#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CSVParser {
 public:
  std::vector<std::string> parse_line(const std::string& line) {
    // TODO: Parse CSV line handling:
    // - Basic comma separation
    // - Quoted fields (may contain commas)
    // - Escaped quotes within fields

    std::vector<std::string> fields;
    std::string current_field;
    bool in_quotes = false;

    for (size_t i = 0; i < line.length(); ++i) {
      char c = line[i];

      if (c == '"') {
        // Check if this is an escaped quote (two consecutive quotes)
        if (in_quotes && i + 1 < line.length() && line[i + 1] == '"') {
          current_field += '"';  // Add one quote to the field
          ++i;                   // Skip the next quote
        } else {
          // Toggle quote mode
          in_quotes = !in_quotes;
        }
      } else if (c == ',' && !in_quotes) {
        // End of field (only if not inside quotes)
        fields.push_back(current_field);
        current_field.clear();
      } else {
        // Regular character - add to current field
        current_field += c;
      }
    }

    // Don't forget the last field
    fields.push_back(current_field);

    return fields;
  }

  void print_parsed(const std::vector<std::string>& fields) {
    for (size_t i = 0; i < fields.size(); ++i) {
      std::cout << "Field " << i << ": '" << fields[i] << "'" << std::endl;
    }
  }
};

int main() {
  CSVParser parser;

  // Test cases
  std::string simple = "John,Doe,30,Engineer";
  std::string quoted = "John,\"Doe, Jr.\",30,\"Software Engineer\"";
  std::string escaped = "John,\"He said \"\"Hello\"\"\",30,Engineer";

  std::cout << "Simple CSV:" << std::endl;
  parser.print_parsed(parser.parse_line(simple));

  std::cout << "\nQuoted CSV:" << std::endl;
  parser.print_parsed(parser.parse_line(quoted));

  std::cout << "\nEscaped Quotes CSV:" << std::endl;
  parser.print_parsed(parser.parse_line(escaped));

  return 0;
}