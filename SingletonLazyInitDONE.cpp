#include <iostream>

class SingletonLazy {
private:
    static SingletonLazy* instance;
    SingletonLazy() {}
public:
    static SingletonLazy* getInstance() {
        if (!instance) {
            instance = new SingletonLazy();
        }
        return instance;
    }
};

SingletonLazy* SingletonLazy::instance = nullptr;

int main() {
    SingletonLazy* instance1 = SingletonLazy::getInstance();
    SingletonLazy* instance2 = SingletonLazy::getInstance();
    return 0;
}
