#include <iostream>
#include <string>
using namespace std;
class Charger {
public:
    virtual void charge() = 0;
    virtual ~Charger() = default;
};

class ArmenianSocket {
public:
    void provideElectricity() {
        std::cout << "Electricity provided from European socket." << std::endl;
    }
};

class SocketAdapter : public Charger {
private:
    ArmenianSocket* europeanSocket;
public:
    SocketAdapter(ArmenianSocket* socket) : europeanSocket(socket) {}

    void charge() override {
        cout << "Using adapter for compatibility." << endl;
        europeanSocket->provideElectricity();
    }
};

class USCharger : public Charger {
public:
    void charge() override {
        cout << "Charging using US socket." << endl;
    }
};

int main() {
    USCharger usCharger;
    cout << "Using US charger directly:\n";
    usCharger.charge();

    ArmenianSocket armenianSocket;
    SocketAdapter adapter(&armenianSocket);
    cout << "\nUsing US charger in Armenia with adapter:\n";
    adapter.charge();

    return 0;
}
