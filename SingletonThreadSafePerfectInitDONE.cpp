#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
	static Singleton* instance;    
	static mutex mtx;       

	Singleton() {
		cout << "Singleton instance created" << endl;
	}

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* getInstance() {
		if (instance == nullptr) { 
			lock_guard<mutex> lock(mtx);
			if (instance == nullptr) { 
				instance = new Singleton();
			}
		}
		return instance;
	}

	void showMessage() {
		cout << "Hello from Singleton!" << endl;
	}
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
	Singleton* s1 = Singleton::getInstance();
	s1->showMessage();

	Singleton* s2 = Singleton::getInstance();
	s2->showMessage();

	cout << "Are s1 and s2 the same instance? "
		<< (s1 == s2 ? "Yes" : "No") << endl;

	return 0;
}
