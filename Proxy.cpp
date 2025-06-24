#include <iostream>
#include <memory>
#include <unordered_set>
using namespace std;

// Interface for any payment system
class IPayment {
public:
    virtual void pay(int userId, int amount) = 0;
    virtual ~IPayment() = default;
};

// Real object: a real BankAccount
class BankAccount : public IPayment {
private:
    int balance;
public:
    BankAccount(int initialBalance) : balance(initialBalance) {
        cout << "[BankAccount] Created with balance: " << balance << "\n";
    }

    void pay(int userId, int amount) override {
        if (amount > balance) {
            cout << "[BankAccount] Insufficient funds for user " << userId << ": " << amount << "\n";
        } else {
            balance -= amount;
            cout << "[BankAccount] User " << userId << " paid " << amount << ". New balance: " << balance << "\n";
        }
    }
};

// Proxy: adds logging, lazy initialization, and access control
class CreditCard : public IPayment {
private:
    unique_ptr<BankAccount> realAccount;
    int initialBalance;
    unordered_set<int> authorizedUsers;

    bool isAuthorized(int userId) {
        return authorizedUsers.count(userId) > 0;
    }

public:
    CreditCard(int initialBalance) : initialBalance(initialBalance) {
        // Allow user IDs 101 and 202
        authorizedUsers.insert(101);
        authorizedUsers.insert(202);
    }

    void pay(int userId, int amount) override {
        cout << "[CreditCard] User " << userId << " is trying to pay " << amount << "\n";

        if (!isAuthorized(userId)) {
            cout << "[CreditCard] ❌ Access denied for user " << userId << "\n";
            return;
        }

        if (!realAccount) {
            cout << "[CreditCard] Lazy initializing BankAccount...\n";
            realAccount = make_unique<BankAccount>(initialBalance);
        }

        realAccount->pay(userId, amount);
    }
};

int main() {
    CreditCard card(1000);  // Proxy is ready

    card.pay(101, 300);     // ✅ Authorized user
    card.pay(999, 100);     // ❌ Unauthorized user
    card.pay(202, 400);     // ✅ Authorized user
    card.pay(101, 400);     // ✅ Succeeds or fails based on balance

    return 0;
}
