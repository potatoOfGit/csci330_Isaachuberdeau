#include <chrono>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class ContainerBenchmark {
 private:
  vector<int> vec;
  list<int> lst;

  double measureTime(auto func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
  }

 public:
  void initialize() {
    for (int i = 0; i < 10000; i++) {
      vec.push_back(i);
      lst.push_back(i);
    }
  }

  void benchmarkFrontInsertion() {
    cout << "\n=== Front Insertion (1000 elements) ===" << endl;

    vector<int> tempVec = vec;
    double vecTime = measureTime([&]() {
      for (int i = 0; i < 1000; i++) {
        tempVec.insert(tempVec.begin(), i);
      }
    });

    list<int> tempLst = lst;
    double lstTime = measureTime([&]() {
      for (int i = 0; i < 1000; i++) {
        tempLst.push_front(i);
      }
    });

    cout << "Vector: " << vecTime << " ms" << endl;
    cout << "List: " << lstTime << " ms" << endl;
    cout << "Winner: " << (lstTime < vecTime ? "List" : "Vector") << endl;
  }

  void benchmarkBackInsertion() {
    cout << "\n=== Back Insertion (1000 elements) ===" << endl;

    vector<int> tempVec = vec;
    double vecTime = measureTime([&]() {
      for (int i = 0; i < 1000; i++) {
        tempVec.push_back(i);
      }
    });

    list<int> tempLst = lst;
    double lstTime = measureTime([&]() {
      for (int i = 0; i < 1000; i++) {
        tempLst.push_back(i);
      }
    });

    cout << "Vector: " << vecTime << " ms" << endl;
    cout << "List: " << lstTime << " ms" << endl;
    cout << "Winner: " << (vecTime < lstTime ? "Vector" : "List") << endl;
  }

  void benchmarkMiddleAccess() {
    cout << "\n=== Middle Element Access (1000 accesses) ===" << endl;

    double vecTime = measureTime([&]() {
      for (int i = 0; i < 1000; i++) {
        int val = vec[vec.size() / 2];
      }
    });

    cout << "Vector: " << vecTime << " ms" << endl;
    cout << "List: Not supported (requires iteration)" << endl;
    cout << "Winner: Vector" << endl;
  }
};

int main() {
  ContainerBenchmark benchmark;

  cout << "Initializing containers with 10,000 elements..." << endl;
  benchmark.initialize();

  benchmark.benchmarkFrontInsertion();
  benchmark.benchmarkBackInsertion();
  benchmark.benchmarkMiddleAccess();

  return 0;
}