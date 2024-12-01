#include <iostream>
#include <string>

class Person {
private:
    std::string name;
public:
    Person(const std::string& name) : name(name) {}

    Person(const Person& other) : name(other.name) {}

    ~Person() {}

    void print() const {
        std::cout << name << std::endl;
    }
};

class Apartment {
private:
    Person** residents;
    size_t residentCount;
public:
    Apartment() : residents(nullptr), residentCount(0) {}

    Apartment(const Apartment& other) {
        residentCount = other.residentCount;
        if (residentCount > 0) {
            residents = new Person * [residentCount];
            for (size_t i = 0; i < residentCount; i++) {
                residents[i] = new Person(*other.residents[i]);
            }
        }
        else {
            residents = nullptr;
        }
    }

    ~Apartment() {
        for (size_t i = 0; i < residentCount; i++) {
            delete residents[i];
        }
        delete[] residents;
    }
    void addResident(const Person& person) {
        Person** newResidents = new Person * [residentCount + 1];
        for (size_t i = 0; i < residentCount; i++) {
            newResidents[i] = residents[i];
        }
        newResidents[residentCount] = new Person(person);
        delete[] residents;
        residents = newResidents;
        residentCount++;
    }

    void printResidents() const {
        std::cout << "Residents in the apartment:" << std::endl;
        for (size_t i = 0; i < residentCount; i++) {
            residents[i]->print();
        }
    }
};

class Building {
private:
    Apartment* apartments;
    size_t apartmentCount;
public:
    Building(size_t count) : apartmentCount(count) {
        apartments = new Apartment[apartmentCount];
    }

    Building(const Building& other) {
        apartmentCount = other.apartmentCount;
        apartments = new Apartment[apartmentCount];
        for (size_t i = 0; i < apartmentCount; i++) {
            apartments[i] = other.apartments[i];
        }
    }
    ~Building() {
        delete[] apartments;
    }

    void addResidentToApartment(size_t apartmentIndex, const Person& person) {
        if (apartmentIndex < apartmentCount) {
            apartments[apartmentIndex].addResident(person);
        }
        else {
            std::cout << "Out of bounds" << std::endl;
        }
    }

    void printApartments() const {
        for (size_t i = 0; i < apartmentCount; ++i) {
            std::cout << "Apartment " << i + 1 << ":" << std::endl;
            apartments[i].printResidents();
        }
    }
};

int main() {
    Building building(3);
    building.addResidentToApartment(0, Person("Ivan"));
    building.addResidentToApartment(0, Person("Anton "));
    building.addResidentToApartment(1, Person("Andrey"));
    building.addResidentToApartment(2, Person("Eva"));
    building.printApartments();
}
