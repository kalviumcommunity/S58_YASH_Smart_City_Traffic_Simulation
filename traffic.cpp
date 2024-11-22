#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

// Enum for traffic light states
enum class TrafficLightState { Red, Yellow, Green };

// Abstract base class for movable entities
class MovableEntity {
public:
    virtual void move(int distance) = 0; // Pure virtual function
    virtual void stop() = 0;
    virtual int getPosition() const = 0;
    virtual int getId() const = 0;
    virtual ~MovableEntity() = default;
};

// Vehicle class inherits from MovableEntity
class Vehicle : public MovableEntity {
public:
    // Constructor
    Vehicle(int id, int speed) : id(id), speed(speed), position(0) {
        ++vehicleCount;
        std::cout << "Vehicle " << id << " created with speed " << speed << " km/h.\n";
    }

    // Destructor
    ~Vehicle() {
        --vehicleCount;
        std::cout << "Vehicle " << id << " destroyed.\n";
    }

    void move(int distance) override {
        if (speed > 0) {
            position += distance;
        }
    }

    void stop() override {
        speed = 0;
        std::cout << "Vehicle " << id << " has stopped at position " << position << ".\n";
    }

    int getPosition() const override {
        return position;
    }

    int getId() const override {
        return id;
    }

    void accelerate(int increment) {
        speed += increment;
        std::cout << "Vehicle " << id << " accelerated to " << speed << " km/h.\n";
    }

    static int getVehicleCount() {
        return vehicleCount;
    }

private:
    int id;
    int speed;
    int position;

    static int vehicleCount; // Static member to count vehicles
};

// Initialize the static member
int Vehicle::vehicleCount = 0;

// TrafficLight class
class TrafficLight {
public:
    // Constructor
    TrafficLight(int id, TrafficLightState initialState = TrafficLightState::Green)
        : id(id), state(initialState) {
        std::cout << "Traffic Light " << id << " created with initial state "
                  << (state == TrafficLightState::Green ? "Green" : "Other") << ".\n";
    }

    // Destructor
    ~TrafficLight() {
        std::cout << "Traffic Light " << id << " destroyed.\n";
    }

    void changeState(TrafficLightState newState) {
        state = newState;
    }

    TrafficLightState getState() const {
        return state;
    }

    int getId() const {
        return id;
    }

private:
    int id;
    TrafficLightState state;
};

// Abstract base class for simulation management
class SimulationManager {
public:
    virtual void simulateStep() = 0; // Pure virtual function
    virtual ~SimulationManager() = default;
};

// Concrete TrafficSimulation class
class TrafficSimulation : public SimulationManager {
public:
    // Constructor
    TrafficSimulation(const std::string& roadName, int roadLength, int lanes)
        : roadName(roadName), roadLength(roadLength), lanes(lanes) {
        std::cout << "TrafficSimulation created for road: " << roadName
                  << " with length " << roadLength << " and " << lanes << " lanes.\n";
    }

    // Destructor
    ~TrafficSimulation() {
        std::cout << "TrafficSimulation for road " << roadName << " destroyed.\n";
    }

    void addVehicle(std::shared_ptr<MovableEntity> vehicle) {
        vehicles.push_back(vehicle);
    }

    void addTrafficLight(std::shared_ptr<TrafficLight> trafficLight) {
        trafficLights.push_back(trafficLight);
    }

    void simulateStep() override {
        static int step = 1;

        std::cout << "\n--- Simulation Step " << step << " ---\n";

        // Move vehicles and simulate actions
        for (auto& vehicle : vehicles) {
            if (vehicle->getPosition() < roadLength / 2) {
                vehicle->move(10); // Move by 10 units
                std::cout << "Vehicle " << vehicle->getId()
                          << " moved to position " << vehicle->getPosition() << ".\n";
            } else {
                vehicle->stop(); // Stop if position >= roadLength / 2
            }
        }

        // Manage traffic light states
        for (auto& light : trafficLights) {
            TrafficLightState newState = (step % 5 == 0) ? TrafficLightState::Yellow : TrafficLightState::Green;
            light->changeState(newState);

            std::cout << "Traffic Light " << light->getId()
                      << " is now " << (newState == TrafficLightState::Yellow ? "Yellow" : "Green") << ".\n";
        }

        ++step;
    }

private:
    std::string roadName;
    int roadLength;
    int lanes;
    std::vector<std::shared_ptr<MovableEntity>> vehicles;
    std::vector<std::shared_ptr<TrafficLight>> trafficLights;
};

// Main function
int main() {
    // Use smart pointers to manage memory
    std::vector<std::shared_ptr<MovableEntity>> vehicles = {
        std::make_shared<Vehicle>(1, 50),
        std::make_shared<Vehicle>(2, 30),
        std::make_shared<Vehicle>(3, 40),
        std::make_shared<Vehicle>(4, 20),
        std::make_shared<Vehicle>(5, 60),
    };

    std::vector<std::shared_ptr<TrafficLight>> trafficLights = {
        std::make_shared<TrafficLight>(1),
        std::make_shared<TrafficLight>(2),
        std::make_shared<TrafficLight>(3),
    };

    // Create a traffic simulation
    TrafficSimulation simulation("Main Street", 1000, 2);

    // Add vehicles and traffic lights to the simulation
    for (const auto& vehicle : vehicles) {
        simulation.addVehicle(vehicle);
    }
    for (const auto& light : trafficLights) {
        simulation.addTrafficLight(light);
    }

    // Run the simulation for 10 steps
    for (int i = 0; i < 10; ++i) {
        simulation.simulateStep();
    }

    return 0;
}
