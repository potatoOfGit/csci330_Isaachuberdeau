#include <iostream>
#include <memory>
#include <string>

class DataProcessor {
 private:
  std::unique_ptr<int[]> data;
  size_t size;

 public:
  DataProcessor(size_t n) : size(n), data(std::make_unique<int[]>(n)) {
    for (size_t i = 0; i < n; ++i) {
      data[i] = static_cast<int>(i * i);
    }
  }

  void print_data() const {
    for (size_t i = 0; i < size; ++i) {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }

  int get_value(size_t index) const {
    if (index < size) return data[index];
    return -1;
  }
};

int main() {
  DataProcessor processor(5);
  processor.print_data();

  DataProcessor processor2 = std::move(processor);  // Test move semantics
  processor2.print_data();

  std::cout << "Value at index 3: " << processor2.get_value(3) << std::endl;
  return 0;
}