#include <iostream>

class Patient {
    private:
    int id;
    std::string name;
    std::string disease;
    int costPerDay;
    int daysInHospital;
    std::string hospitalAdmitted;
    // Add Vector of Doctors (Patients can be treated by multiple doctor)   

    public:
    // Default constructor
    Patient(std::string name, std::string disease, int costPerDay, int daysInHospital)
        : name{ name }
        , disease{ disease }
        , costPerDay{ costPerDay }
        , daysInHospital { daysInHospital } 
    {}

    /* Rule of Five */
    

    // Getter methods
    int getId() const {
        return id;
    }

    std::string getName() {
        return name;
    }

    std::string getDisease() {
        return disease;
    }

    int getCostPerDay() {
        return costPerDay;
    }

    int getBill() const {
        return daysInHospital * costPerDay;
    }
    
    // Setter methods
    void setId(int id) {
        this->id = id;
    }
    
    void updateDays(int days) {
        daysInHospital = days;
    }

};