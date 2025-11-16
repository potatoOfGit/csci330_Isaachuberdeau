#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

using DataPoint = std::variant<int, double, std::string>;
using ProcessingResult = std::tuple<size_t, size_t, double>;
using DataSummary =
    std::tuple<std::optional<double>, std::optional<double>, size_t>;

class TimedOperation {
 private:
  std::chrono::steady_clock::time_point start_time;
  std::string operation_name;

 public:
  TimedOperation(const std::string& name)
      : start_time(std::chrono::steady_clock::now()), operation_name(name) {}

  ~TimedOperation() {
    std::cout << operation_name << " completed in " << elapsed_ms() << "ms"
              << std::endl;
  }

  double elapsed_ms() const {
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = end_time - start_time;
    return duration.count();
  }
};

class DataAnalyzer {
 private:
  std::vector<DataPoint> data;

 public:
  void add_data_point(const DataPoint& point) { data.push_back(point); }

  void load_from_strings(const std::vector<std::string>& raw_data) {
    for (const auto& str : raw_data) {
      try {
        size_t pos;
        int int_val = std::stoi(str, &pos);
        if (pos == str.length()) {
          data.push_back(int_val);
          continue;
        }
      } catch (...) {
      }

      try {
        size_t pos;
        double double_val = std::stod(str, &pos);
        if (pos == str.length()) {
          data.push_back(double_val);
          continue;
        }
      } catch (...) {
      }

      data.push_back(str);
    }
  }

  ProcessingResult process_data() {
    TimedOperation timer("Data processing");

    size_t processed = 0;
    size_t errors = 0;

    for (const auto& point : data) {
      try {
        std::visit([](auto&& arg) {}, point);
        processed++;
      } catch (...) {
        errors++;
      }
    }

    return std::make_tuple(processed, errors, timer.elapsed_ms());
  }

  DataSummary calculate_numeric_summary() {
    double min_val = std::numeric_limits<double>::max();
    double max_val = std::numeric_limits<double>::lowest();
    size_t count = 0;

    for (const auto& point : data) {
      std::visit(
          [&](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
              double val = static_cast<double>(arg);
              if (val < min_val) min_val = val;
              if (val > max_val) max_val = val;
              count++;
            } else if constexpr (std::is_same_v<T, double>) {
              if (arg < min_val) min_val = arg;
              if (arg > max_val) max_val = arg;
              count++;
            }
          },
          point);
    }

    if (count == 0) {
      return std::make_tuple(std::nullopt, std::nullopt, 0);
    }

    return std::make_tuple(std::optional<double>(min_val),
                           std::optional<double>(max_val), count);
  }

  template <typename T>
  std::vector<T> get_data_of_type() {
    std::vector<T> result;
    for (const auto& point : data) {
      if (std::holds_alternative<T>(point)) {
        result.push_back(std::get<T>(point));
      }
    }
    return result;
  }

  std::optional<std::string> export_summary() {
    if (data.empty()) {
      return std::nullopt;
    }

    std::ostringstream oss;
    oss << "Data Summary:\n";
    oss << "Total data points: " << data.size() << "\n";

    auto [min_val, max_val, numeric_count] = calculate_numeric_summary();
    if (numeric_count > 0) {
      oss << std::fixed << std::setprecision(5);
      oss << "Numeric data points: " << numeric_count << "\n";
      if (min_val) oss << "Min value: " << *min_val << "\n";
      if (max_val) oss << "Max value: " << *max_val << "\n";
    }

    auto strings = get_data_of_type<std::string>();
    oss << "String data points: " << strings.size() << "\n";

    return oss.str();
  }
};

int main() {
  DataAnalyzer analyzer;

  std::vector<std::string> raw_data = {"42",      "3.14159",     "hello", "99",
                                       "2.71828", "invalid_num", "world"};

  analyzer.load_from_strings(raw_data);

  auto [processed, errors, time_ms] = analyzer.process_data();
  auto [min_val, max_val, numeric_count] = analyzer.calculate_numeric_summary();

  assert(processed == 7);
  assert(errors == 0);
  assert(time_ms > 0);

  assert(min_val.has_value() && *min_val == 2.71828);
  assert(max_val.has_value() && *max_val == 99);
  assert(numeric_count == 4);

  auto strings = analyzer.get_data_of_type<std::string>();
  assert(strings.size() == 3);

  auto summary = analyzer.export_summary();
  assert(summary.has_value());

  std::cout << "\nAll tests passed!\n\n";
  std::cout << *summary << std::endl;

  return 0;
}