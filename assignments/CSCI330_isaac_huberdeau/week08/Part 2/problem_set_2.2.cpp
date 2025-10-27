#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class FileProcessor {
 private:
  std::ifstream file;
  std::string filename;

 public:
  // Constructor - acquire resource (open file)
  FileProcessor(const std::string& fname) : filename(fname) {
    file.open(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file: " + filename);
    }
    std::cout << "File '" << filename << "' opened successfully." << std::endl;
  }

  // Destructor - release resource (close file)
  ~FileProcessor() {
    if (file.is_open()) {
      file.close();
      std::cout << "File '" << filename << "' closed automatically."
                << std::endl;
    }
  }

  // Delete copy constructor and assignment (RAII best practice)
  FileProcessor(const FileProcessor&) = delete;
  FileProcessor& operator=(const FileProcessor&) = delete;

  int count_lines() {
    file.clear();                  // Clear any error flags
    file.seekg(0, std::ios::beg);  // Reset to beginning

    int lines = 0;
    std::string line;
    while (std::getline(file, line)) {
      lines++;
    }

    file.clear();                  // Clear EOF flag
    file.seekg(0, std::ios::beg);  // Reset position
    return lines;
  }

  int count_words() {
    file.clear();
    file.seekg(0, std::ios::beg);

    int words = 0;
    std::string word;
    while (file >> word) {
      words++;
    }

    file.clear();
    file.seekg(0, std::ios::beg);
    return words;
  }

  int count_characters() {
    file.clear();
    file.seekg(0, std::ios::beg);

    int characters = 0;
    char ch;
    while (file.get(ch)) {
      characters++;
    }

    file.clear();
    file.seekg(0, std::ios::beg);
    return characters;
  }
};

// Test function that demonstrates RAII even with exceptions
void test_file_processing(const std::string& filename) {
  try {
    FileProcessor processor(filename);

    std::cout << "Lines: " << processor.count_lines() << std::endl;
    std::cout << "Words: " << processor.count_words() << std::endl;
    std::cout << "Characters: " << processor.count_characters() << std::endl;

    // Simulate an exception
    if (processor.count_lines() > 100) {
      throw std::runtime_error("File too large!");
    }

  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
    // File should still be properly closed due to RAII
  }
}

int main() {
  // Create a test file
  std::cout << "Creating test file..." << std::endl;
  std::ofstream testFile("test.txt");
  testFile << "Hello World\n";
  testFile << "This is a test file.\n";
  testFile << "It has multiple lines and words.\n";
  testFile.close();

  std::cout << "\n--- Test 1: Valid file ---" << std::endl;
  test_file_processing("test.txt");

  std::cout << "\n--- Test 2: Invalid file ---" << std::endl;
  test_file_processing("nonexistent.txt");

  std::cout << "\n--- Test 3: Scope-based cleanup ---" << std::endl;
  {
    try {
      FileProcessor fp("test.txt");
      std::cout << "Lines: " << fp.count_lines() << std::endl;
    } catch (const std::exception& e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
    // Destructor called automatically when fp goes out of scope
  }
  std::cout << "Scope exited, file should be closed now." << std::endl;

  return 0;
}