#include <iostream>
#include <map>
#include <string>

using namespace std;

class WordCounter {
 private:
  map<string, int> wordMap;

 public:
  void readInput() {
    string word;
    cout << "Enter words (type 'quit' to stop):" << endl;

    while (cin >> word && word != "quit") {
      wordMap[word]++;
    }
  }

  void displayFrequencies() {
    cout << "\nWord Frequencies (alphabetical order):" << endl;
    for (auto& pair : wordMap) {
      cout << pair.first << ": " << pair.second << endl;
    }
  }

  void displayMostFrequent() {
    if (wordMap.empty()) {
      cout << "\nNo words to analyze." << endl;
      return;
    }

    string mostFrequentWord;
    int maxCount = 0;

    for (auto& pair : wordMap) {
      if (pair.second > maxCount) {
        maxCount = pair.second;
        mostFrequentWord = pair.first;
      }
    }

    cout << "\nMost frequent word: " << mostFrequentWord << " (" << maxCount
         << " times)" << endl;
  }
};

int main() {
  WordCounter counter;
  counter.readInput();
  counter.displayFrequencies();
  counter.displayMostFrequent();

  return 0;
}