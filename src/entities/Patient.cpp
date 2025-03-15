#ifndef PATIENT_CPP
#define PATIENT_CPP
#include <iostream>
#include <vector>
#include "Doctor.cpp"  
#include "Nurse.cpp"

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
    std::vector<Doctor*> doctors; 
    Nurse* primaryNurse; 
    Status status;

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
    int getHospitalId() const { return hospitalId; }
    Nurse* getPrimaryNurse() const { return primaryNurse; }
    std::vector<Doctor*> getDoctors() const { return doctors; }

    // Setter methods
    void setId(int id) { this->id = id; }
    void setDaysInHospital(int days) { this->daysInHospital = days; }
    void setHospitalId(int hid) { hospitalId = hid; hospitalAdmitted = std::to_string(hid); }
    void addDoctor(Doctor* d) { doctors.push_back(d); }
    void setPrimaryNurse(Nurse* n) { primaryNurse = n; }
    
    void setStatus(Status s) { status = s; }
    Status getStatus() const { return status; }
    void incrementDays() { daysInHospital++; }

};

#endif