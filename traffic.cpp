#include <iostream>
#include <string>
#include <vector>

class Vehicle {
public:
    Vehicle(int id, int speed) : id(id), speed(speed), position(0) {}
    void move(int distance) {
        position += distance;
    }
    void stop() {
        speed = 0;
    }
    int getPosition() {
        return position;
    }
private:
    int id;
    int speed;
    int position;
};

class TrafficLight {
public:
    TrafficLight(int id) : id(id), state("green") {}
    void change_state(std::string state) {
        this->state = state;
    }
    std::string getState() {
        return state;
    }
private:
    int id;
    std::string state;
};

class Road {
public:
    Road(std::string name, int length, int lanes) : name(name), length(length), lanes(lanes) {}
    void add_vehicle(Vehicle vehicle) {
        vehicles.push_back(vehicle);
    }
    void remove_vehicle(Vehicle vehicle) {
        // implement removal logic
    }
private:
    std::string name;
    int length;
    int lanes;
    std::vector<Vehicle> vehicles;
};

int main() {
    Road road("Main Street", 1000, 2);
    Vehicle vehicle1(1, 50);
    Vehicle vehicle2(2, 30);
    road.add_vehicle(vehicle1);
    road.add_vehicle(vehicle2);

    TrafficLight traffic_light(1);

    // simulate traffic flow
    for (int i = 0; i < 10; i++) {
        vehicle1.move(10);
        vehicle2.move(5);
        traffic_light.change_state("yellow");
        std::cout << "Vehicle 1 position: " << vehicle1.getPosition() << std::endl;
        std::cout << "Vehicle 2 position: " << vehicle2.getPosition() << std::endl;
        std::cout << "Traffic light state: " << traffic_light.getState() << std::endl;
    }

    return 0;
}