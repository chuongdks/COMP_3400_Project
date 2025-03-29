#ifndef PATIENT_CPP
#define PATIENT_CPP
#include <iostream>
#include <vector>
#include "./Doctor.cpp"  
#include "./Nurse.cpp"

class Patient {
    public:
    enum class Status { Dead, Alive, Critical, Recovering, FUBAR };

    private:
    int id;
    std::string name;
    std::string disease;
    int costPerDay;
    int daysInHospital;
    std::string hospitalAdmitted;
    int hospitalId; 

    Doctor* primaryDoctor;           // Only 1 primary doctor
    std::vector<Doctor*> doctors;    // Multiple treating doctors
    Nurse* primaryNurse; 
    Status status;

    public:
    // Default constructor
    Patient(std::string name, std::string disease, int costPerDay)
        : name{ name }
        , disease{ disease }
        , costPerDay{ costPerDay }
    {}
    
    // Getter methods
    int getId() const { return id; }
    std::string getName() { return name; }
    std::string getDisease() { return disease; }
    int getCostPerDay() { return costPerDay; }
    int getdaysInHospital() { return daysInHospital; }
    int getBill() const { return daysInHospital * costPerDay; }
    int getHospitalId() const { return hospitalId; }
    Nurse* getPrimaryNurse() const { return primaryNurse; }
    std::vector<Doctor*> getDoctors() const { return doctors; }
    Status getStatus() const { return status; }

    // Setter methods
    void setId(int id) { this->id = id; }
    void setDaysInHospital(int days) { this->daysInHospital = days; }
    void setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
    void setPrimaryNurse(Nurse* n) { primaryNurse = n; }
    void setStatus(Status s) { status = s; }
    void incrementDays() { daysInHospital++; }

    /* Other methods */
    // Assign a primary doctor
    void setPrimaryDoctor(Doctor* doctor) {
        primaryDoctor = doctor;
    }

    // Add doctors to Patient
    void addDoctor(Doctor* doctor) {
        doctors.push_back(doctor);
    }

    // Display all doctors treating this patient
    void displayDoctors() {
        std::cout << "Patient: " << name << " is treated by:\n";
        if (primaryDoctor) {
            std::cout << "- Primary Doctor: " << primaryDoctor->getName() << "\n";
        }
        for (auto doctor : doctors) {
            if (doctor != primaryDoctor) {
                std::cout << "- " << doctor->getName() << "\n";
            }
        }
    }
};

#endif