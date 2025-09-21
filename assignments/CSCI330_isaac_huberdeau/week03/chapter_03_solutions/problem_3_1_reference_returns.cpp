#include <cstdio>

struct BankAccount {
    double balance;
    int account_number;
};

// Function that returns a const reference to the balance
const double& get_balance(const BankAccount& account) {
    return account.balance;
}

// Function that returns a reference to the matching account
BankAccount& get_account_for_update(BankAccount accounts[], int account_number) {
    return accounts[account_number - 1];  // Assumes valid account_number
}

int main() {
    BankAccount accounts[3] = {
        {1000.50, 1},
        {2500.75, 2}, 
        {750.25, 3}
    };

    // Display account 2's balance
    printf("Account 2 balance: $%.2f\n", get_balance(accounts[1]));

    // Modify account 1's balance to 1200.00
    get_account_for_update(accounts, 1).balance = 1200.00;

    // Display all account balances
    printf("Updated balances:\n");
    for (int i = 0; i < 3; ++i) {
        printf("Account %d: $%.2f\n", accounts[i].account_number, accounts[i].balance);
    }

    return 0;
}
