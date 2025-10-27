#include <iostream>
#include <vector>
using namespace std;

int main() {
  std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};

  // TODO: Display all temperatures
  for (int i = 0; i < temperatures.size(); i++) {
    std::cout << temperatures[i] << ", ";
  }
  std::cout << endl;
  // TODO: Calculate average
  double sum = 0;
  double average;
  for (int j = 0; j < temperatures.size(); j++) {
    sum += temperatures[j];
  }
  average = sum / temperatures.size();
  std::cout << "Average Temp: " << average << endl;
  // TODO: Count above average
  std::cout << "Temps above average: ";
  for (int k = 0; k < temperatures.size(); k++) {
    if (temperatures[k] > average) {
      std::cout << temperatures[k] << ", ";
    }
  }
  std::cout << endl;
  // TODO: Add 2.0 to all temperatures
  for (int l = 0; l < temperatures.size(); l++) {
    temperatures[l] += 2.0;
  }
  // TODO: Display modified temperatures
  for (int p = 0; p < temperatures.size(); p++) {
    std::cout << temperatures[p] << ",";
  }

  return 0;
}