#include <fstream>
#include <iostream>
#include <string>

struct Logger {
  virtual ~Logger() = default;
  virtual void log(const std::string& message) const = 0;

  // Convenience function implemented in base
  virtual void log_error(const std::string& message) const {
    log("ERROR: " + message);
  }
};

struct ConsoleLogger : Logger {
  void log(const std::string& message) const override {
    std::cout << "[Console] " << message << "\n";
  }
};

struct FileLogger : Logger {
  std::string filename;

  FileLogger(const std::string& file) : filename(file) {}

  void log(const std::string& message) const override {
    std::ofstream out(filename, std::ios::app);
    if (out) {
      out << "[File] " << message << "\n";
    }
  }
};

struct SilentLogger : Logger {
  // Implement this - it should do nothing but satisfy the interface
  void log(const std::string& message) const override {}
};