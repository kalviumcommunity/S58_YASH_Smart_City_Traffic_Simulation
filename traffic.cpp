#include <iostream>
#include <string>
#include <vector>

class Vehicle {
public:
    Vehicle(int id, int speed) : id(id), speed(speed), position(0) {
        ++vehicleCount;  // Increment the static vehicle count when a new vehicle is created
    }
    
    ~Vehicle() {
        --vehicleCount;  // Decrement the static vehicle count when a vehicle is destroyed
    }

    void move(int distance) {
        if (speed > 0) {
            position += distance;
        }
    }

    void stop() {
        speed = 0;
        std::cout << "Vehicle " << id << " has stopped at position " << position << std::endl;
    }

    void speedUp(int increment) {
        speed += increment;
        std::cout << "Vehicle " << id << " speed increased to " << speed << " km/h\n";
    }

    int getPosition() const {
        return position;
    }

    int getSpeed() const {
        return speed;
    }

    static int getVehicleCount() {
        return vehicleCount;
    }

    bool operator==(const Vehicle& other) const {
        return id == other.id;
    }

private:
    int id;
    int speed;
    int position;

    // Static member to track the number of vehicles
    static int vehicleCount;
};

// Initialize the static variable
int Vehicle::vehicleCount = 0;

class TrafficLight {
public:
    TrafficLight(int id) : id(id), state("green") {}

    void change_state(std::string state) {
        this->state = state;
    }

    std::string getState() const {
        return state;
    }

private:
    int id;
    std::string state;
};

class Road {
public:
    Road(std::string name, int length, int lanes) : name(name), length(length), lanes(lanes) {}

    void add_vehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    void remove_vehicle(Vehicle* vehicle) {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (*it == vehicle) {
                vehicles.erase(it);
                break;
            }
        }
    }

private:
    std::string name;
    int length;
    int lanes;
    std::vector<Vehicle*> vehicles;
};

int main() {
    // Create an array of Vehicle objects using dynamic memory
    const int numVehicles = 5;
    Vehicle* vehicles = new Vehicle[numVehicles] {
        Vehicle(1, 50),
        Vehicle(2, 30),
        Vehicle(3, 40),
        Vehicle(4, 20),
        Vehicle(5, 60)
    };

    // Create an array of TrafficLight objects using dynamic memory
    const int numTrafficLights = 3;
    TrafficLight* trafficLights = new TrafficLight[numTrafficLights] {
        TrafficLight(1),
        TrafficLight(2),
        TrafficLight(3)
    };

    // Create a road
    Road road("Main Street", 1000, 2);

    // Add vehicles to the road
    for (int i = 0; i < numVehicles; i++) {
        road.add_vehicle(&vehicles[i]);
    }

    // Print the total number of vehicles using the static member function
    std::cout << "Total number of vehicles: " << Vehicle::getVehicleCount() << std::endl;

    // Simulate traffic flow
    for (int i = 0; i < 10; i++) {
        std::cout << "\nSimulation Step " << i + 1 << ":\n";

        // Move each vehicle and increase speed
        for (int j = 0; j < numVehicles; j++) {
            if (vehicles[j].getPosition() < 50) {
                vehicles[j].move(10);  // Move by 10 units
                std::cout << "Vehicle " << (j + 1) << " position: " << vehicles[j].getPosition() << std::endl;

                vehicles[j].speedUp(5);  // Speed up by 5 km/h
            } else {
                vehicles[j].stop();  // Stop if position >= 50
            }
        }

        // Change traffic light states
        for (int j = 0; j < numTrafficLights; j++) {
            if (i < 5) {
                trafficLights[j].change_state("yellow");
            } else {
                trafficLights[j].change_state("green");
            }
            std::cout << "Traffic light " << (j + 1) << " state: " << trafficLights[j].getState() << std::endl;
        }
    }

    // Clean up dynamically allocated memory
    delete[] vehicles;
    delete[] trafficLights;

    return 0;
}
