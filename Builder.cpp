#include <iostream>
#include <string>
using namespace std;

class House {
    string foundation;
    string walls;
    bool isGardenEnabled;
    bool isPoolEnabled;
    House(string foundation, string walls, bool garden, bool pool) : 
        foundation(foundation), walls(walls), isGardenEnabled(garden), 
        isPoolEnabled(pool){}
public:
    string getFoundation() const { return foundation; }
    string getWalls() const { return walls; }
    bool hasGarden() const { return isGardenEnabled; }
    bool hasPool() const { return isPoolEnabled; }

    friend class HouseBuilder;
    //House(const House&) = delete;
    //House& operator=(const House&) = delete;
};


class HouseBuilder {
    string foundation;
    string walls;
    bool isGardenEnabled = false;
    bool isPoolEnabled = false;
public:
    HouseBuilder(const string& foundation, const string& walls)
        : foundation(foundation), walls(walls) {}
    HouseBuilder& setGardenEnabled(bool enabled) {
        isGardenEnabled = enabled;
        return *this;
    }
    HouseBuilder& setPoolEnabled(bool enabled) {
        isPoolEnabled = enabled;
        return *this;
    }
    House build() {
        return House(foundation, walls, isGardenEnabled, isPoolEnabled);
    }
};
int main() {
    House myHouse = HouseBuilder("Concrete", "Brick")
        .setGardenEnabled(true)
        .setPoolEnabled(true)
        .build();

    std::cout << "House Configuration:\n";
    std::cout << "Foundation: " << myHouse.getFoundation() << "\n";
    std::cout << "Walls: " << myHouse.getWalls() << "\n";
    std::cout << "Swimming Pool Enabled: " << (myHouse.hasPool() ? "Yes" : "No") << "\n";
    std::cout << "Garden Enabled: " << (myHouse.hasGarden() ? "Yes" : "No") << "\n";
    return 0;
}
