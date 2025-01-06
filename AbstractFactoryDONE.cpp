#include <iostream>
using namespace std;
class Vehicle {
public:
	virtual void specs() const = 0;
	virtual ~Vehicle() = default;
};
class Car : public Vehicle {
public:
	void specs() const override {
		cout << "This is a car\n";
	}
};
class Truck : public Vehicle {
public:
	void specs() const override {
		cout << "This is a truck\n";
	}
};

class VehicleFactory {
public:
	virtual unique_ptr <Vehicle> createCar() const = 0;
	virtual unique_ptr <Vehicle> createTruck() const = 0;
	virtual ~VehicleFactory() = default;
};
class TeslaFactory : public VehicleFactory {
	unique_ptr <Vehicle> createCar() const override {
		return make_unique<Car>();
	}
	unique_ptr <Vehicle> createTruck() const override {
		return make_unique<Truck>();
	}
};
class ToyotaFactory : public VehicleFactory {
	unique_ptr <Vehicle> createCar() const override {
		return make_unique<Car>();
	}
	unique_ptr <Vehicle> createTruck() const override {
		return make_unique<Truck>();
	}
};
void produceVehicles(const VehicleFactory& factory) {
	auto car = factory.createCar();
	auto truck = factory.createTruck();
	car->specs();
	truck->specs();
}
int main() {
	TeslaFactory teslaFactory;
	ToyotaFactory toyotaFactory;
	std::cout << "Producing Tesla vehicles:\n";
	produceVehicles(teslaFactory);

	std::cout << "\nProducing Toyota vehicles:\n";
	produceVehicles(toyotaFactory);

	return 0;
}


