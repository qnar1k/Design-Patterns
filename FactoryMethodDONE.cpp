#include <iostream>
#include <memory>
using namespace std;

class Vehicle {
public:
    virtual void drive() = 0;
    virtual ~Vehicle() = default;
};
class Car : public Vehicle {
public:
    virtual void drive() override {
        cout << "This is a car\n";
    }
};
class Truck : public Vehicle {
public:
    virtual void drive() override {
        cout << "This is a truck\n";
    }
};
class VehicleFactory {
public:
    virtual unique_ptr<Vehicle> createVehicle() = 0;
    virtual ~VehicleFactory() = default;
};
class CarFactory : public VehicleFactory {
public:
    virtual unique_ptr<Vehicle> createVehicle() {
        return make_unique<Car>();
    }
};
class TruckFactory : public VehicleFactory {
public:
    virtual unique_ptr<Vehicle> createVehicle() {
        return make_unique<Truck>();
    }
};
int main() {
    unique_ptr<VehicleFactory> carFactory = make_unique<CarFactory>();
    unique_ptr<Vehicle> myCar = carFactory->createVehicle();
    myCar->drive();

    unique_ptr<VehicleFactory> truckFactory = make_unique<TruckFactory>();
    unique_ptr<Vehicle> myTruck = truckFactory->createVehicle();
    myTruck->drive();

    return 0;
}
