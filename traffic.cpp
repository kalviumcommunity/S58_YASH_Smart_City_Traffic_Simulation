#include <iostream>
#include <string>
#include <vector>

// Enum for traffic light states to ensure strict control
enum class TrafficLightState { Red, Yellow, Green };

class Vehicle {
public:
    Vehicle(int id, int speed) : id(id), speed(speed), position(0) {
        ++vehicleCount;  // Increment the static vehicle count when a new vehicle is created
    }

    ~Vehicle() {
        --vehicleCount;  // Decrement the static vehicle count when a vehicle is destroyed
    }

    // Public interface for moving the vehicle
    void move(int distance) {
        if (distance > 0 && speed > 0) {
            position += distance;
        } else {
            std::cerr << "Invalid move operation for Vehicle " << id << "\n";
        }
    }

    void stop() {
        speed = 0;
        std::cout << "Vehicle " << id << " has stopped at position " << position << std::endl;
    }

    void speedUp(int increment) {
        if (increment > 0) {
            speed += increment;
            std::cout << "Vehicle " << id << " speed increased to " << speed << " km/h\n";
        } else {
            std::cerr << "Invalid speed increment for Vehicle " << id << "\n";
        }
    }

    // Getters (No direct access to private members)
    int getPosition() const {
        return position;
    }

    int getSpeed() const {
        return speed;
    }

    int getId() const {
        return id;
    }

    static int getVehicleCount() {
        return vehicleCount;
    }

    // Operator to compare vehicles by their ID
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
    TrafficLight(int id) : id(id), state(TrafficLightState::Green) {}

    // Change the state of the traffic light
    void changeState(TrafficLightState newState) {
        state = newState;
    }

    // Get the current state
    TrafficLightState getState() const {
        return state;
    }

private:
    int id;
    TrafficLightState state;
};

class Road {
public:
    Road(std::string name, int length, int lanes) 
        : name(std::move(name)), length(length), lanes(lanes) {}

    void addVehicle(Vehicle* vehicle) {
        if (vehicle) {
            vehicles.push_back(vehicle);
        } else {
            std::cerr << "Invalid vehicle to add on the road.\n";
        }
    }

    void removeVehicle(Vehicle* vehicle) {
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
        road.addVehicle(&vehicles[i]);
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
                std::cout << "Vehicle " << vehicles[j].getId() 
                          << " position: " << vehicles[j].getPosition() << std::endl;

                vehicles[j].speedUp(5);  // Speed up by 5 km/h
            } else {
                vehicles[j].stop();  // Stop if position >= 50
            }
        }

        // Change traffic light states
        for (int j = 0; j < numTrafficLights; j++) {
            if (i < 5) {
                trafficLights[j].changeState(TrafficLightState::Yellow);
            } else {
                trafficLights[j].changeState(TrafficLightState::Green);
            }
            std::cout << "Traffic light " << (j + 1) 
                      << " state: " << (trafficLights[j].getState() == TrafficLightState::Yellow ? "Yellow" : "Green") 
                      << std::endl;
        }
    }

    // Clean up dynamically allocated memory
    delete[] vehicles;
    delete[] trafficLights;

    return 0;
}
