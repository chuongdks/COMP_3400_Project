#include <iostream>

class Patient {
    private:
    int id;
    std::string name;
    std::string disease;
    
    int costPerDay;
    int daysInHospital;

    public:
    // Default constructor
    Patient(int id, std::string name, std::string disease)
        : id{ id }
        , name{ name }
        , disease{ disease }
        , costPerDay{ 0 }
        , daysInHospital { 0 } 
    {}

    // Getter methods
    int getID() const {
        return id;
    }

    std::string getName() {
        return name;
    }

    std::string getDisease() {
        return name;
    }

    int getBill() const {
        return daysInHospital * costPerDay;
    }
    
    // Setter methods
    void updateDays(int days) {
        daysInHospital = days;
    }

};