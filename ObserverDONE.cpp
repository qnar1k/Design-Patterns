#include <iostream>
#include <vector>
#include <memory>

class User {
public:
    virtual void notify(const std::string& appName) = 0;
    virtual ~User() = default;
};

class Application {
private:
    std::vector<std::shared_ptr<User>> users;
    std::string appName;

public:
    Application(const std::string& name) : appName(name) {}

    void addUser(std::shared_ptr<User> user) {
        users.push_back(user);
    }

    void removeUser(std::shared_ptr<User> user) {
        users.erase(std::remove(users.begin(), users.end(), user), users.end());
    }

    void notifyUsers() {
        for (const auto& user : users) {
            user->notify(appName);
        }
    }

    void releaseUpdate() {
        std::cout << "Update released for " << appName << "!\n";
        notifyUsers();
    }
};

class ConcreteUser : public User {
private:
    std::string name;

public:
    explicit ConcreteUser(const std::string& name) : name(name) {}

    void notify(const std::string& appName) override {
        std::cout << name << " received notification: " << appName << " has a new update.\n";
    }
};

int main() {
    auto app = std::make_shared<Application>("ChatGPT App");

    auto user1 = std::make_shared<ConcreteUser>("Alice");
    auto user2 = std::make_shared<ConcreteUser>("Bob");

    app->addUser(user1);
    app->addUser(user2);

    app->releaseUpdate();

    app->removeUser(user1);
    app->releaseUpdate();

    return 0;
}
