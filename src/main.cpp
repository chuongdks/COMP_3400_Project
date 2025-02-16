// Hospital.h
#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <string>
#include <vector>
#include "Patient.h"
#include "Doctor.h"
#include "Nurse.h"

class Hospital {
private:
    std::string name;
    int locationID;
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Nurse> nurses;
public:
    Hospital(std::string name, int locationID);
    void admitPatient(Patient p);
    void dischargePatient(int patientID);
};
#endif

// Pharmacy.h
#ifndef PHARMACY_H
#define PHARMACY_H
#include <string>
class Pharmacy {
private:
    std::string name;
public:
    Pharmacy(std::string name);
    void billHospital(std::string hospitalName, double amount);
};
#endif

// Patient.h
#ifndef PATIENT_H
#define PATIENT_H
#include <string>
class Patient {
private:
    int patientID;
    std::string name;
    std::string disease;
    int daysAdmitted;
public:
    Patient(int id, std::string name, std::string disease);
    void updateDaysAdmitted(int days);
};
#endif

// Doctor.h
#ifndef DOCTOR_H
#define DOCTOR_H
#include <string>
class Doctor {
private:
    int doctorID;
    std::string name;
public:
    Doctor(int id, std::string name);
};
#endif

// Nurse.h
#ifndef NURSE_H
#define NURSE_H
#include <string>
class Nurse {
private:
    int nurseID;
    std::string name;
public:
    Nurse(int id, std::string name);
};
#endif

// main.cpp
#include <iostream>
#include "Hospital.h"
#include "Pharmacy.h"
#include "Patient.h"
#include "Doctor.h"
#include "Nurse.h"

int main() {
    Hospital h1("Windsor General", 1);
    Patient p1(101, "John Doe", "Flu");
    Doctor d1(1, "Dr. Smith");
    Nurse n1(201, "Nurse Jane");
    Pharmacy ph1("HealthPharma");
    
    h1.admitPatient(p1);
    ph1.billHospital("Windsor General", 500.0);
    
    std::cout << "Hospital Management System Initialized." << std::endl;
    return 0;
}
