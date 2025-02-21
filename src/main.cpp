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

    // Create Patients
    Patient* patient1 = new Patient("John Doe", "Flu", 50);
    Patient* patient2 = new Patient("Jane Smith", "Covid-19", 100);

    // Admit patients to a hospital
    manager.admitPatientToHospital(1, patient1);
    manager.admitPatientToHospital(1, patient2);

    // Display hospitals and their patients
    manager.displayAllHospitals();

    // Remove a patient
    manager.dischargePatientFromHospital(1, 1);

    // Remove Hospital
    manager.removeHospital(1);

    return 0;
}

