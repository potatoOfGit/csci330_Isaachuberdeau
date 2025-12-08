#include <iostream>
#include <vector>

// TODO: Implement this function using iterators
template <typename Container, typename T>
bool contains(const Container& container, const T& value) {
  // Return true if container contains value, false otherwise
  // Hint: Use iterators to search through the container
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (*it == value) {
      return true;
    }
  }

  return false;
}

// TODO: Implement this function using iterators
template <typename Container, typename T>
size_t count_occurrences(const Container& container, const T& value) {
  // Count how many times value appears in container
  // Use iterators to traverse and count
  size_t count = 0;
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (*it == value) {
      count++;
    }
  }
  return count;
}

// TODO: Implement this function using iterators
template <typename Container>
void print_reverse(const Container& container) {
  // Print container elements in reverse order
  // Hint: Some containers support reverse iterators (rbegin, rend)
  for (auto it = container.rbegin(); it != container.rend(); ++it) {
    std::cout << *it << " ";
  }
}

int main() {
  std::vector<int> data{1, 3, 7, 3, 9, 3, 5};

  // Test your functions
  std::cout << "Contains 7: " << contains(data, 7) << "\n";
  std::cout << "Contains 4: " << contains(data, 4) << "\n";
  std::cout << "Count of 3: " << count_occurrences(data, 3) << "\n";
  std::cout << "Reverse: ";
  print_reverse(data);
  std::cout << "\n";

  return 0;
}