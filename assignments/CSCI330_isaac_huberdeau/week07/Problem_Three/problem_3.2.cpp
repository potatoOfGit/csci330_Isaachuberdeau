#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Design 1: Student class
class Student {
 private:
  string name;
  double gpa;

 public:
  Student(const string& name, double gpa) : name(name), gpa(gpa) {}

  // Question: Are these good operator overloads?
  Student operator+(const Student& other) const {
    // "Adding" students by averaging their GPAs?
    return Student(name + " & " + other.name, (gpa + other.gpa) / 2);
  }

  bool operator<(const Student& other) const {
    // Comparing by GPA for sorting
    return gpa < other.gpa;
  }

  Student& operator<<(const string& course) {
    // "Enrolling" student in course?
    cout << name << " enrolled in " << course << endl;
    return *this;
  }

  string get_name() const { return name; }
  double get_gpa() const { return gpa; }
};

// Design 2: BankAccount class
class BankAccount {
 private:
  string account_number;
  double balance;

 public:
  BankAccount(const string& account_number, double initial_balance = 0.0)
      : account_number(account_number), balance(initial_balance) {}

  // Question: Are these good operator overloads?
  BankAccount operator+(double amount) const {
    // Adding money to account
    return BankAccount(account_number, balance + amount);
  }

  BankAccount operator-(const BankAccount& other) const {
    // Transferring money between accounts?
    return BankAccount(account_number, balance - other.balance);
  }

  bool operator>(const BankAccount& other) const {
    // Comparing account balances
    return balance > other.balance;
  }

  double get_balance() const { return balance; }
  string get_account_number() const { return account_number; }
};

// TODO: For each questionable operator overload above, suggest a better
// alternative Write your analysis and improvements here:

/*
Your analysis:

Design 1 (Student class):
- operator+(): [Good/Bad?] Why?
- operator<(): [Good/Bad?] Why?
- operator<<(): [Good/Bad?] Why?
- Better alternatives:

Design 2 (BankAccount class):
- operator+(): [Good/Bad?] Why?
- operator-(): [Good/Bad?] Why?
- operator>(): [Good/Bad?] Why?
- Better alternatives:
*/

int main() {
  // Test the designs and think about whether they feel natural
  Student alice("Alice", 3.8);
  Student bob("Bob", 3.2);

  // Does this make sense?
  Student combined = alice + bob;
  cout << "Combined student: " << combined.get_name()
       << " with GPA: " << combined.get_gpa() << endl;

  // Does this make sense?
  alice << "Mathematics" << "Physics";

  BankAccount account1("12345", 1000.0);
  BankAccount account2("67890", 500.0);

  // Does this make sense?
  BankAccount after_deposit = account1 + 200.0;
  cout << "After deposit: $" << after_deposit.get_balance() << endl;

  // Does this make sense?
  BankAccount after_transfer = account1 - account2;
  cout << "After transfer: $" << after_transfer.get_balance() << endl;

  return 0;
}