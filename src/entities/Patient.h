#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <vector>

class Doctor;       // Forward declaration
class Nurse;        // Forward declaration

class Patient {
public:
    enum class Status { Dead, Alive, Critical, Recovering, FUBAR };

private:
    int id;
    std::string name;
    std::string disease;
    int costPerDay;
    int daysInHospital;
    int hospitalId;
    std::string hospitalAdmitted;
    
    Doctor* primaryDoctor;
    std::vector<Doctor*> doctors;
    Nurse* primaryNurse;
    Status status;

public:
    // Constructor
    Patient(std::string name, std::string disease, int costPerDay);

    // Getter methods
    int getId() const;
    std::string getName() const;
    std::string getDisease() const;
    int getCostPerDay() const;
    int getDaysInHospital() const;
    int getBill() const;
    int getHospitalId() const;
    Nurse* getPrimaryNurse() const;
    std::vector<Doctor*> getDoctors() const;
    Status getStatus() const;

    // Setter methods
    void setId(int id);
    void setDaysInHospital(int days);
    void setHospitalId(int hid);
    void setPrimaryNurse(Nurse* n);
    void setStatus(Status s);
    void incrementDays();

    // Other methods
    void setPrimaryDoctor(Doctor* doctor);
    void addDoctorToPatient(Doctor* doctor);
    void displayDoctors();
};

#endif