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
    // Doctor* primaryDoctor;           // Only 1 primary doctor
    // std::vector<Doctor*> doctors;    // Multiple treating doctors

    public:
    // Default constructor
    Patient(std::string name, std::string disease, int costPerDay)
        : name{ name }
        , disease{ disease }
        , costPerDay{ costPerDay }
    {}

    /* Rule of Five */
    

    // Getter methods
    int getId() const { return id; }
    std::string getName() { return name; }
    std::string getDisease() { return disease; }
    int getCostPerDay() { return costPerDay; }
    int getdaysInHospital() { return daysInHospital; }
    int getBill() const { return daysInHospital * costPerDay; }
    
    // Setter methods
    void setId(int id) { this->id = id; }
    void setDaysInHospital(int days) { this->daysInHospital = days; }

};