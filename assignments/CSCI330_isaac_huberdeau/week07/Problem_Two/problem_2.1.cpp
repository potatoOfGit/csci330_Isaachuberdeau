#include <iomanip>
#include <iostream>
using namespace std;

class Money {
 private:
  int cents;  // Store as cents to avoid floating-point issues

 public:
  // Constructor: Money(dollars, cents) or Money(total_cents)
  Money(int dollars = 0, int cents = 0) : cents(dollars * 100 + cents) {}
  explicit Money(int total_cents) : cents(total_cents) {}

  // TODO: Implement these operators

  static Money fromCents(int totalCents) {
    Money m;
    m.cents = totalCents;
    return m;
  }

  // Addition
  Money operator+(const Money& other) const {
    // Your implementation here
    return Money::fromCents(cents + other.cents);
  }

  // Subtraction
  Money operator-(const Money& other) const {
    // Your implementation here
    return Money::fromCents(cents - other.cents);
  }

  // Compound addition
  Money& operator+=(const Money& other) {
    // Your implementation here
    cents += other.cents;
    return *this;
  }

  // Compound subtraction
  Money& operator-=(const Money& other) {
    // Your implementation here
    cents -= other.cents;
    return *this;
  }

  // Equality comparison
  bool operator==(const Money& other) const {
    // Your implementation here
    return (cents == other.cents);
  }

  // Less than comparison
  bool operator<(const Money& other) const {
    // Your implementation here
    return (cents < other.cents);
  }

  // Display function (we'll make this an operator later)
  void print() const {
    cout << "$" << cents / 100 << "." << setfill('0') << setw(2) << cents % 100;
  }

  // Getter for testing
  int get_cents() const { return cents; }
};

int main() {
  Money wallet(25, 50);  // $25.50
  Money coffee(4, 75);   // $4.75
  Money lunch(12, 30);   // $12.30

  cout << "Starting amount: ";
  wallet.print();
  cout << endl;

  // Test your operators
  Money after_coffee = wallet - coffee;
  cout << "After buying coffee: ";
  after_coffee.print();
  cout << endl;

  after_coffee -= lunch;
  cout << "After buying lunch: ";
  after_coffee.print();
  cout << endl;

  Money total_spent = coffee + lunch;
  cout << "Total spent: ";
  total_spent.print();
  cout << endl;

  // Test comparisons
  if (after_coffee < Money(10, 0)) {
    cout << "Running low on money!" << endl;
  }

  return 0;
}