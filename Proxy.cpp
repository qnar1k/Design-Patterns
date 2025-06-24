#include <iostream>
#include <memory>
using namespace std;

// Interface all payment methods implement
class IPayment {
public:
    virtual void pay(int amount) = 0;
    virtual ~IPayment() = default;
};

// Real object: resource-heavy bank account
class BankAccount : public IPayment {
private:
    int balance;
public:
    BankAccount(int initialBalance) : balance(initialBalance) {
        cout << "[BankAccount] Created with balance: " << balance << "\n";
    }

    void pay(int amount) override {
        if (amount > balance) {
            cout << "[BankAccount] Insufficient funds for payment of " << amount << "\n";
        }
        else {
            balance -= amount;
            cout << "[BankAccount] Payment of " << amount << " processed. New balance: " << balance << "\n";
        }
    }
};

// Proxy object: adds logging and lazy initialization
class CreditCard : public IPayment {
private:
    unique_ptr<BankAccount> realAccount;
    int initialBalance;
public:
    CreditCard(int initialBalance) : initialBalance(initialBalance) {}

    void pay(int amount) override {
        cout << "[CreditCard] Requesting payment of " << amount << "\n";

        if (!realAccount) {
            cout << "[CreditCard] Lazy initializing BankAccount...\n";
            realAccount = make_unique<BankAccount>(initialBalance);
        }

        realAccount->pay(amount);
    }
};

int main() {
    // Client uses proxy (CreditCard), not direct BankAccount
    CreditCard card(1000); // Proxy created, but not the BankAccount yet

    card.pay(300); // First call creates BankAccount lazily
    card.pay(500); // Uses existing BankAccount
    card.pay(300); // Insufficient funds example

    return 0;
}
