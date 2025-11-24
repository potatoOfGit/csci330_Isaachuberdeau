#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

class MapBenchmark {
 private:
  map<int, int> orderedMap;
  unordered_map<int, int> unorderedMap;
  vector<int> randomNumbers;
  vector<int> searchKeys;

  template <typename Func>
  double measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
  }

 public:
  void generateData() {
    cout << "Generating 100,000 random integers..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);

    for (int i = 0; i < 100000; i++) {
      randomNumbers.push_back(dis(gen));
    }

    cout << "Generating 10,000 search keys..." << endl;
    for (int i = 0; i < 10000; i++) {
      searchKeys.push_back(randomNumbers[dis(gen) % randomNumbers.size()]);
    }
  }

  void benchmarkInsertion() {
    cout << "\n=== Insertion Benchmark (100,000 elements) ===" << endl;

    auto mapInsert = [&]() {
      for (int num : randomNumbers) {
        orderedMap[num] = num * 2;
      }
    };
    double mapTime = measureTime(mapInsert);

    auto unorderedInsert = [&]() {
      for (int num : randomNumbers) {
        unorderedMap[num] = num * 2;
      }
    };
    double unorderedMapTime = measureTime(unorderedInsert);

    cout << fixed << setprecision(2);
    cout << "std::map insertion time: " << mapTime << " ms" << endl;
    cout << "std::unordered_map insertion time: " << unorderedMapTime << " ms"
         << endl;

    double speedup = mapTime / unorderedMapTime;
    cout << "Speedup: " << speedup << "x ";
    cout << "(unordered_map is " << (speedup > 1 ? "faster" : "slower") << ")"
         << endl;
  }

  void benchmarkLookup() {
    cout << "\n=== Lookup Benchmark (10,000 searches) ===" << endl;

    auto mapLookup = [&]() {
      for (int key : searchKeys) {
        auto it = orderedMap.find(key);
      }
    };
    double mapTime = measureTime(mapLookup);

    auto unorderedLookup = [&]() {
      for (int key : searchKeys) {
        auto it = unorderedMap.find(key);
      }
    };
    double unorderedMapTime = measureTime(unorderedLookup);

    cout << fixed << setprecision(2);
    cout << "std::map lookup time: " << mapTime << " ms" << endl;
    cout << "std::unordered_map lookup time: " << unorderedMapTime << " ms"
         << endl;

    double speedup = mapTime / unorderedMapTime;
    cout << "Speedup: " << speedup << "x ";
    cout << "(unordered_map is " << (speedup > 1 ? "faster" : "slower") << ")"
         << endl;
  }

  void displaySummary() {
    cout << "\n=== Summary ===" << endl;
    cout << "std::map uses a balanced binary tree (O(log n) operations)"
         << endl;
    cout << "std::unordered_map uses a hash table (O(1) average operations)"
         << endl;
    cout << "unordered_map is typically faster for insertion and lookup"
         << endl;
    cout << "map keeps elements sorted by key" << endl;
  }
};

int main() {
  MapBenchmark benchmark;

  benchmark.generateData();
  benchmark.benchmarkInsertion();
  benchmark.benchmarkLookup();
  benchmark.displaySummary();

  return 0;
}