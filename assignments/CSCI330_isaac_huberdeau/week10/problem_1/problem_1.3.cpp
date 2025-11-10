#include <fstream>
#include <iostream>
#include <memory>
#include <string>

class FileManager {
 private:
  std::unique_ptr<FILE, decltype(&std::fclose)> file;

 public:
  FileManager(const std::string& filename, const std::string& mode)
      : file(std::fopen(filename.c_str(), mode.c_str()), &std::fclose) {}

  bool write(const std::string& data) {
    if (!is_open()) return false;
    return std::fputs(data.c_str(), file.get()) != EOF;
  }

  std::string read_line() {
    if (!is_open()) return "";
    char buffer[1024];
    if (std::fgets(buffer, sizeof(buffer), file.get())) {
      return std::string(buffer);
    }
    return "";
  }

  bool is_open() const { return file != nullptr; }
};

int main() {
  {
    FileManager writer("test.txt", "w");
    if (writer.is_open()) {
      writer.write("Hello, Smart Pointers!\n");
      writer.write("RAII is awesome!\n");
    }
  }

  {
    FileManager reader("test.txt", "r");
    if (reader.is_open()) {
      std::cout << "Line 1: " << reader.read_line();
      std::cout << "Line 2: " << reader.read_line();
    }
  }

  return 0;
}