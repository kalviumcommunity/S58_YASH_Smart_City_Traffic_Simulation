#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Abstract base class for movable entities
class MovableEntity {
public:
    virtual void move(int distance) = 0; // Pure virtual function
    virtual void stop() = 0;
    virtual int getPosition() const = 0;
    virtual int getId() const = 0;
    virtual void accelerate(int increment) = 0; // Added to base class
    virtual ~MovableEntity() = default;
};

// Vehicle class inherits from MovableEntity
class Vehicle : public MovableEntity {
public:
    Vehicle(int id, int speed) : id(id), speed(speed), position(0) {
        ++vehicleCount;
        std::cout << "Vehicle " << id << " created with speed " << speed << " km/h.\n";
    }

    virtual ~Vehicle() {
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

    virtual void accelerate(int increment) override { // Implement in base class
        speed += increment;
        std::cout << "Vehicle " << id << " accelerated to " << speed << " km/h.\n";
    }

    static int getVehicleCount() {
        return vehicleCount;
    }

protected:
    int id;
    int speed;
    int position;

private:
    static int vehicleCount; // Static member to count vehicles
};

// Initialize static member
int Vehicle::vehicleCount = 0;

// Car class inherits from Vehicle
class Car : public Vehicle {
public:
    Car(int id, int speed) : Vehicle(id, speed) {
        std::cout << "Car " << id << " created.\n";
    }

    ~Car() override {
        std::cout << "Car " << id << " destroyed.\n";
    }

    void move(int distance) override {
        Vehicle::move(distance);
        std::cout << "Car " << id << " moved quickly to position " << position << ".\n";
    }

    void accelerate(int increment) override { // Override the virtual accelerate
        speed += increment * 2; // Cars accelerate faster
        std::cout << "Car " << id << " accelerated to " << speed << " km/h.\n";
    }
};

// Main function
int main() {
    std::vector<std::shared_ptr<MovableEntity>> vehicles = {
        std::make_shared<Car>(1, 50),
        std::make_shared<Car>(2, 30),
        std::make_shared<Car>(3, 40),
    };

    for (const auto& vehicle : vehicles) {
        vehicle->move(10);
        vehicle->accelerate(5); // Now valid since accelerate is in the base class
        vehicle->stop();
    }

    std::cout << "Total vehicles created: " << Vehicle::getVehicleCount() << "\n";

    return 0;
}
