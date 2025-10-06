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

struct Application {
  Logger* logger;

  Application(Logger* log) : logger(log) {}

  void run() {
    logger->log("Application started");
    do_some_work();
    logger->log("Application finished");
  }

 private:
  void do_some_work() {
    logger->log("Doing important work...");
    // Simulate potential error
    logger->log_error("Something went wrong!");
    logger->log("Recovered from error");
  }
};

int main() {
  std::cout << "====Run with Console Logger====\n";
  ConsoleLogger consoleLog;
  Application app1(&consoleLog);
  app1.run();

  std::cout << "====Run with File Logger====\n";
  FileLogger fileLog("app.log");
  Application app2(&fileLog);
  app2.run();

  std::cout << "====Run with Silent Logger====\n";
  SilentLogger silentLog;
  Application app3(&silentLog);
  app3.run();

  return 0;
}