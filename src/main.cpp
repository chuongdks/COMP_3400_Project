#include <iostream>
#include "HospitalManager.cpp"
#include "./entities/Pharmacy.cpp"
#include "./database/Database.cpp"

int main() {
    // Create and Initialize the Database and table 
    const char* dbPath = "../db/hospital.db";
    Database db(dbPath);         // Create Database instance
    db.createTable();

    // Hospital manager object
    HospitalManager manager(db); // Pass db to HospitalManager

    // Add some hospitals
    manager.addHospital("City Hospital 1");
    manager.addHospital("City Hospital 2");

    // Create Patients, Doctor and NUrses
    Patient* patient1 = new Patient("John Doe", "Flu", 50);
    Patient* patient2 = new Patient("Jane Smith", "Covid-19", 100);

    Doctor* doctor1 = new Doctor("Dr. Smith", "Covid-19");
    Doctor* doctor2 = new Doctor("Dr. Sin", "Proctologists");

    Nurse* nurse1 = new Nurse("Nurse Joy");
    Nurse* nurse2 = new Nurse("Nurse Bubble Head");

    // Admit patients, doctors and nurse to a hospital
    manager.admitPatientToHospital(1, patient1);
    manager.admitPatientToHospital(1, patient2);
    manager.assignDoctorToHospital(1, doctor1);
    manager.assignDoctorToHospital(1, doctor2);
    manager.assignNurseToHospital(1, nurse1);
    manager.assignNurseToHospital(1, nurse1);

    // Display hospitals and their patients
    manager.displayAllHospitals();

    // // Remove a patient
    // manager.dischargePatientFromHospital(1, 1);

    // // Remove Hospital
    // manager.removeHospital(1);

    return 0;
}

