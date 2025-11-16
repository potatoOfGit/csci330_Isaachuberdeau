#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <variant>

using ConfigValue = std::variant<int, double, std::string, bool>;

class ConfigParser {
 private:
  std::map<std::string, std::string> raw_data;

 public:
  ConfigParser(const std::map<std::string, std::string>& data)
      : raw_data(data) {}

  template <typename T>
  std::optional<T> get_value(const std::string& key) {
    auto it = raw_data.find(key);
    if (it == raw_data.end()) {
      return std::nullopt;
    }

    const std::string& value = it->second;

    if constexpr (std::is_same_v<T, int>) {
      try {
        size_t pos;
        int result = std::stoi(value, &pos);
        if (pos == value.length()) {
          return result;
        }
      } catch (...) {
      }
      return std::nullopt;
    } else if constexpr (std::is_same_v<T, double>) {
      try {
        size_t pos;
        double result = std::stod(value, &pos);
        if (pos == value.length()) {
          return result;
        }
      } catch (...) {
      }
      return std::nullopt;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return value;
    } else if constexpr (std::is_same_v<T, bool>) {
      if (value == "true" || value == "1") {
        return true;
      } else if (value == "false" || value == "0") {
        return false;
      }
      return std::nullopt;
    }
  }

  template <typename T>
  T get_value_or(const std::string& key, const T& default_value) {
    auto result = get_value<T>(key);
    return result.value_or(default_value);
  }

  std::map<std::string, ConfigValue> get_all_parsed() {
    std::map<std::string, ConfigValue> result;

    for (const auto& [key, value] : raw_data) {
      if (auto int_val = get_value<int>(key); int_val) {
        result[key] = *int_val;
      } else if (auto double_val = get_value<double>(key); double_val) {
        result[key] = *double_val;
      } else if (auto bool_val = get_value<bool>(key); bool_val) {
        result[key] = *bool_val;
      } else {
        result[key] = value;
      }
    }

    return result;
  }
};

int main() {
  std::map<std::string, std::string> config_data = {
      {"port", "8080"},
      {"host", "localhost"},
      {"timeout", "30.5"},
      {"debug", "true"},
      {"invalid_number", "not_a_number"}};

  ConfigParser parser(config_data);

  // Should successfully parse
  assert(parser.get_value<int>("port") == 8080);
  assert(parser.get_value<std::string>("host") == "localhost");
  assert(parser.get_value<double>("timeout") == 30.5);

  // Should return nullopt for invalid parsing
  assert(!parser.get_value<int>("invalid_number").has_value());

  // Should use defaults
  assert(parser.get_value_or<int>("missing_key", 3000) == 3000);

  std::cout << "All tests passed!" << std::endl;

  return 0;
}