#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

class SetOperations {
 private:
  set<int> set1;
  set<int> set2;

 public:
  SetOperations(const set<int>& s1, const set<int>& s2) : set1(s1), set2(s2) {}

  set<int> getUnion() {
    vector<int> result;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
              back_inserter(result));
    return set<int>(result.begin(), result.end());
  }

  set<int> getIntersection() {
    vector<int> result;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                     back_inserter(result));
    return set<int>(result.begin(), result.end());
  }

  set<int> getDifference() {
    vector<int> result;
    set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                   back_inserter(result));
    return set<int>(result.begin(), result.end());
  }

  void displaySets() {
    cout << "Set 1: ";
    for (int val : set1) cout << val << " ";
    cout << endl;

    cout << "Set 2: ";
    for (int val : set2) cout << val << " ";
    cout << endl;
  }

  void displayResult(const string& operation, const set<int>& result) {
    cout << operation << ": ";
    for (int val : result) cout << val << " ";
    cout << endl;
  }
};

int main() {
  set<int> s1 = {1, 2, 3, 4, 5};
  set<int> s2 = {4, 5, 6, 7, 8};

  SetOperations ops(s1, s2);

  ops.displaySets();
  cout << endl;

  ops.displayResult("Union", ops.getUnion());
  ops.displayResult("Intersection", ops.getIntersection());
  ops.displayResult("Difference (Set1 - Set2)", ops.getDifference());

  return 0;
}