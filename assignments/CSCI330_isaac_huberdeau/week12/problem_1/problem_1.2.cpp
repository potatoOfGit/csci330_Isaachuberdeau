#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>

using DataValue = std::variant<int, double, std::string>;

class DataProcessor {
 public:
  static std::string describe(const DataValue& data) {
    return std::visit(
        [](auto&& arg) -> std::string {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, int>) {
            return "Integer: " + std::to_string(arg);
          } else if constexpr (std::is_same_v<T, double>) {
            std::ostringstream oss;
            oss << arg;
            return "Double: " + oss.str();
          } else if constexpr (std::is_same_v<T, std::string>) {
            return "String: " + arg;
          }
        },
        data);
  }

  static int calculate_size(const DataValue& data) {
    return std::visit(
        [](auto&& arg) -> int {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, int>) {
            return arg;
          } else if constexpr (std::is_same_v<T, double>) {
            return static_cast<int>(std::round(arg));
          } else if constexpr (std::is_same_v<T, std::string>) {
            return static_cast<int>(arg.length());
          }
        },
        data);
  }
};

int main() {
  DataValue int_data = 42;
  DataValue double_data = 3.14159;
  DataValue string_data = std::string("Hello World");

  assert(DataProcessor::describe(int_data) == "Integer: 42");
  assert(DataProcessor::describe(double_data) == "Double: 3.14159");
  assert(DataProcessor::describe(string_data) == "String: Hello World");

  assert(DataProcessor::calculate_size(int_data) == 42);
  assert(DataProcessor::calculate_size(double_data) == 3);
  assert(DataProcessor::calculate_size(string_data) == 11);

  std::cout << "All tests passed!" << std::endl;

  return 0;
}