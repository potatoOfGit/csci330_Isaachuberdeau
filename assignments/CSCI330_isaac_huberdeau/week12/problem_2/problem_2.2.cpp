#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using BenchmarkResult = std::tuple<double, double, double>;

class Benchmarker {
 public:
  template <typename Func>
  static BenchmarkResult benchmark(Func function, int iterations = 1000) {
    std::vector<double> times;
    times.reserve(iterations);

    for (int i = 0; i < iterations; ++i) {
      auto start = std::chrono::high_resolution_clock::now();
      function();
      auto end = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double, std::milli> duration = end - start;
      times.push_back(duration.count());
    }

    double min_time = std::numeric_limits<double>::max();
    double max_time = std::numeric_limits<double>::lowest();
    double sum_time = 0.0;

    for (double time : times) {
      if (time < min_time) min_time = time;
      if (time > max_time) max_time = time;
      sum_time += time;
    }

    double avg_time = sum_time / iterations;

    return std::make_tuple(min_time, max_time, avg_time);
  }

  static std::string format_results(const BenchmarkResult& results) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6);
    oss << "Min: " << std::get<0>(results) << "ms, "
        << "Max: " << std::get<1>(results) << "ms, "
        << "Avg: " << std::get<2>(results) << "ms";
    return oss.str();
  }

  static std::optional<std::string> compare_results(
      const BenchmarkResult& result1, const BenchmarkResult& result2,
      const std::string& name1 = "Function 1",
      const std::string& name2 = "Function 2") {
    double avg1 = std::get<2>(result1);
    double avg2 = std::get<2>(result2);

    if (avg1 == 0.0 && avg2 == 0.0) {
      return std::nullopt;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    if (avg1 < avg2) {
      double speedup = avg2 / avg1;
      oss << name1 << " is " << speedup << "x faster than " << name2;
    } else if (avg2 < avg1) {
      double speedup = avg1 / avg2;
      oss << name2 << " is " << speedup << "x faster than " << name1;
    } else {
      oss << name1 << " and " << name2 << " have equal average times";
    }

    return oss.str();
  }
};

int main() {
  auto fast_function = []() {
    int sum = 0;
    for (int i = 0; i < 100; ++i) sum += i;
    return sum;
  };

  auto slow_function = []() {
    int sum = 0;
    for (int i = 0; i < 10000; ++i) sum += i;
    return sum;
  };

  auto fast_results = Benchmarker::benchmark(fast_function, 1000);
  auto slow_results = Benchmarker::benchmark(slow_function, 100);

  std::cout << "Fast function: " << Benchmarker::format_results(fast_results)
            << std::endl;
  std::cout << "Slow function: " << Benchmarker::format_results(slow_results)
            << std::endl;

  auto comparison =
      Benchmarker::compare_results(fast_results, slow_results, "Fast", "Slow");
  if (comparison) {
    std::cout << *comparison << std::endl;
  }

  return 0;
}