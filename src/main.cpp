#include <iostream>
#include <string>
#include "HospitalManager.cpp"
#include "./entities/Pharmacy.cpp"
#include "./database/Database.cpp"

using namespace std;

void printMenu() {
    cout << "\nHospital Management System Menu\n";
    cout << "1. Add a new hospital\n";
    cout << "2. Admit a patient\n";
    cout << "3. Assign a doctor\n";
    cout << "4. Assign a nurse\n";
    cout << "5. Display all hospitals\n";
    cout << "6. Discharge a patient\n";
    cout << "7. Display all doctors\n"; 
    cout << "8. Display all nurses\n";  
    cout << "9. Exit\n";              
    cout << "Enter your choice (1-9): "; 
}

int main() {
    // Create and Initialize the Database and table 
    const char* dbPath = "../db/hospital.db";
    Database db(dbPath);         // Create Database instance
    db.createTable();
    HospitalManager manager(db); // Pass db to HospitalManager

    int choice;
    string input;

    while (true) {
        printMenu();
        getline(cin, input); 

        try {
            choice = stoi(input);
        } catch (...) {
            choice = 0; 
        }

        switch (choice) {
            case 1: { // Add a new hospital
                string name;
                cout << "Enter hospital name: ";
                getline(cin, name);
                if (!name.empty()) {
                    manager.addHospital(name);
                } else {
                    cout << "Error: Hospital name cannot be empty.\n";
                }
                break;
            }
            case 2: { // Admit a patient
                int hospital_id, cost;
                string name, disease, temp;

                cout << "Enter hospital ID: ";
                getline(cin, temp);
                try {
                    hospital_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid hospital ID.\n";
                    break;
                }

                cout << "Enter patient name: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "Error: Patient name cannot be empty.\n";
                    break;
                }

                cout << "Enter disease: ";
                getline(cin, disease);
                if (disease.empty()) {
                    cout << "Error: Disease cannot be empty.\n";
                    break;
                }

                cout << "Enter cost per day: ";
                getline(cin, temp);
                try {
                    cost = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid cost.\n";
                    break;
                }

                Patient* patient = new Patient(name, disease, cost);
                manager.admitPatientToHospital(hospital_id, patient);
                delete patient; 
                break;
            }
            case 3: { // Assign a doctor
                int hospital_id;
                string name, role, temp;

                cout << "Enter hospital ID: ";
                getline(cin, temp);
                try {
                    hospital_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid hospital ID.\n";
                    break;
                }

                cout << "Enter doctor name: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "Error: Doctor name cannot be empty.\n";
                    break;
                }

                cout << "Enter doctor role (Primary? Y/N): ";
                getline(cin, role);
                if (role.empty()) {
                    cout << "Error: Role cannot be empty.\n";
                    break;
                }

                Doctor* doctor = new Doctor(name, role);
                manager.assignDoctorToHospital(hospital_id, doctor);
                delete doctor; 
                break;
            }
            case 4: { // Assign a nurse
                int hospital_id;
                string name, temp;

                cout << "Enter hospital ID: ";
                getline(cin, temp);
                try {
                    hospital_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid hospital ID.\n";
                    break;
                }

                cout << "Enter nurse name: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "Error: Nurse name cannot be empty.\n";
                    break;
                }

                Nurse* nurse = new Nurse(name);
                manager.assignNurseToHospital(hospital_id, nurse);
                delete nurse; 
                break;
            }
            case 5: { // Display all hospitals
                manager.displayAllHospitals();
                for (Hospital* h : manager.getHospitals()) {
                    h->updatePatientDays();
                }
                break;
            }
            case 6: { // Discharge a patient
                int hospital_id, patient_id, doctor_id;
                string temp;

                cout << "Enter hospital ID: ";
                getline(cin, temp);
                try {
                    hospital_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid hospital ID.\n";
                    break;
                }

                cout << "Enter patient ID: ";
                getline(cin, temp);
                try {
                    patient_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid patient ID.\n";
                    break;
                }

                cout << "Enter doctor ID to authorize: ";
                getline(cin, temp);
                try {
                    doctor_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid doctor ID.\n";
                    break;
                }

                manager.dischargePatientFromHospital(hospital_id, patient_id, doctor_id);
                break;
            }
            case 7: { // Display all doctors 
                manager.displayAllDoctors();
                break;
            }
            case 8: { // Display all nurses 
                manager.displayAllNurses();
                break;
            }
            case 9: { // Exit
                cout << "Exiting.\n";
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 to 9.\n";
                break;
            }
        }
    }

    return 0; 
}