#include <iostream>

class SingletonEager {
private:
    static SingletonEager instance;
    SingletonEager() {}
public:
    static SingletonEager& getInstance() {
        return instance;
    }
};

SingletonEager SingletonEager::instance;

int main() {
    SingletonEager& instance1 = SingletonEager::getInstance();
    SingletonEager& instance2 = SingletonEager::getInstance();
    return 0;
}
