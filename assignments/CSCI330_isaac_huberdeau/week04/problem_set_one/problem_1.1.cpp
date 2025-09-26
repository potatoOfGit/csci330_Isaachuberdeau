#include <cstdio>
#include <stdexcept>
#include <string>
using namespace std;

class TransactionLogger {
  FILE* logFile;

 public:
  TransactionLogger(const char* filename = "bank_transactions.log") {
    logFile = fopen(filename, "a");
    if (!logFile) throw runtime_error("Could not open log file");
    printf("[RAII Logger] Transaction log opened: %s\n", filename);
  }

  void log(const string& msg) {
    fprintf(logFile, "%s\n", msg.c_str());
    fflush(logFile);
    printf("%s\n", msg.c_str());
  }

  ~TransactionLogger() {
    if (logFile) {
      printf("[RAII Logger] Transaction log closed automatically\n");
      fclose(logFile);
    }
  }
};

class BankAccount {
 protected:
  double balance;
  static int nextAccountNum;
  int accountNum;
  string owner;
  static int createdCount;
  static int destroyedCount;

 public:
  BankAccount(string accountHolder, double bal)
      : accountNum(++nextAccountNum), owner(accountHolder), balance(bal) {
    createdCount++;
    printf("[Constructor] Account #%d created: %s, $%.2f\n", accountNum,
           owner.c_str(), balance);
  }

  virtual ~BankAccount() {
    destroyedCount++;
    printf("[Destructor] Account #%d destroyed: Final balance $%.2f\n",
           accountNum, balance);
  }

  void deposit(double amount) { balance += amount; }
  void withdraw(double amount) { balance -= amount; }

  int getAccountNumber() const { return accountNum; }
  double getBalance() const { return balance; }
  string getOwnerName() const { return owner; }

  static int getCreatedCount() { return createdCount; }
  static int getDestroyedCount() { return destroyedCount; }

  void transferTo(BankAccount& other, double amount,
                  TransactionLogger& logger) {
    char buffer[200];
    snprintf(buffer, sizeof(buffer),
             "[Transaction Log] Transfer initiated: #%d -> #%d, $%.2f",
             accountNum, other.accountNum, amount);
    logger.log(buffer);

    if (amount <= 0 || amount > balance) {
      throw runtime_error("Invalid transfer amount");
    }

    this->withdraw(amount);
    other.deposit(amount);

    printf("[Success] Transfer completed successfully\n");
  }
};

int BankAccount::nextAccountNum = 1000;
int BankAccount::createdCount = 0;
int BankAccount::destroyedCount = 0;

class BusinessAccount : public BankAccount {
 public:
  BusinessAccount(string owner, double bal) : BankAccount(owner, bal) {
    printf("[Constructor] Business Account #%d: %s, $%.2f\n",
           getAccountNumber(), owner.c_str(), bal);
  }
};

int main() {
  printf("=== Banking System with RAII Demo ===\n");

  BankAccount acc1("John Doe", 1000.0);
  BankAccount acc2("Jane Smith", 1500.0);
  BusinessAccount acc3("Acme Corp", 10000.0);

  {
    TransactionLogger logger;
    acc1.transferTo(acc2, 200.0, logger);
  }

  printf(
      "\nSummary: %d accounts created, %d accounts destroyed, 1 transfer "
      "completed\n",
      BankAccount::getCreatedCount(), BankAccount::getDestroyedCount());

  return 0;
}
