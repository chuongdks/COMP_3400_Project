#include <iostream>
#include <string>
#include "HospitalManager.cpp"
#include "PharmacyManager.cpp"
#include "./entities/Pharmacy.cpp"
#include "./database/Database.cpp"

using namespace std;

void printMenu() {
    cout << "\nHospital Management System Menu\n";
    cout << "1. Add a new hospital\n";
    cout << "2. Admit a patient\n";
    cout << "3. Assign a doctor\n";
    cout << "4. Assign a nurse\n";
    cout << "5. Assign a doctor to a patient and vice versa\n";  
    cout << "6. Assign a nurse to a patient and vice versa\n";  
    cout << "7. Display all hospitals\n";
    cout << "8. Discharge a patient\n";
    cout << "9. Display all patients\n"; 
    cout << "10. Display all doctors\n"; 
    cout << "11. Display all nurses\n";  
    cout << "12. Pharmacy Management\n";
    cout << "13. Exit\n";              
    cout << "Enter your choice (1-13): "; 
}

void printPharmacyMenu() {
    cout << "\nPharmacy Management Menu\n";
    cout << "1. Add a new pharmacy\n";
    cout << "2. Display all pharmacies\n";
    cout << "3. Deliver medicine\n";
    cout << "4. View hospital bill\n";
    cout << "5. Clear hospital bill\n";
    cout << "6. Return to main menu\n";
    cout << "Enter your choice (1-6): ";
}

int main() {
    // Create and Initialize the Database and table 
    const char* dbPath = "../db/hospital.db";
    Database db(dbPath);         // Create Database instance
    db.createTable();
    HospitalManager manager(db); // Pass db to HospitalManager
    PharmacyManager pharmManager(db); // Pass db to PharmacyManager

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
            // Add a new hospital
            case 1: { 
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

            // Admit a patient
            case 2: { 
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

            // Assign a doctor
            case 3: { 
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

                cout << "Enter doctor role: ";
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

            // Assign a nurse
            case 4: { 
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

            // Assign a doctor to a patient and vice versa
            case 5: { 
                int hospital_id, doctor_id, patient_id;
                string temp, isPrimary;
            
                cout << "Enter hospital ID: ";
                getline(cin, temp);
                try {
                    hospital_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid hospital ID.\n";
                    break;
                }
            
                cout << "Enter doctor ID: ";
                getline(cin, temp);
                try {
                    doctor_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid doctor ID.\n";
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
            
                cout << "Is this a primary doctor? (Y/N): ";
                getline(cin, isPrimary);
                bool primaryDoctor = (isPrimary == "Y" || isPrimary == "y");
            
                // Assign the doctor to the patient
                manager.assignDoctorToPatient(hospital_id, doctor_id, patient_id, primaryDoctor);
                break;
            }

            // Assign a nurse to a patient and vice versa
            case 6: { 
                int hospital_id, nurse_id, patient_id;
                string temp, isPrimary;
            
                cout << "Enter hospital ID: ";
                getline(cin, temp);
                try {
                    hospital_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid hospital ID.\n";
                    break;
                }
            
                cout << "Enter nurse ID: ";
                getline(cin, temp);
                try {
                    nurse_id = stoi(temp);
                } catch (...) {
                    cout << "Error: Invalid doctor ID.\n";
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
            
                // Assign the doctor to the patient
                manager.assignNurseToPatient(hospital_id, nurse_id, patient_id);
                break;
            }

            // Display all hospitals
            case 7: { 
                manager.displayAllHospitals();
                for (Hospital* h : manager.getHospitals()) {
                    h->updatePatientDays();
                }
                break;
            }

            // Discharge a patient
            case 8: {
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

            // Display all patients in all Hospital
            case 9: { 
                manager.displayAllPatients();
                break;
            }

            // Display all doctors in all Hospital
            case 10: { 
                manager.displayAllDoctors();
                break;
            }

            // Display all nurses in all Hospital
            case 11: { 
                manager.displayAllNurses();
                break;
            }

            // Pharmacy Management
            case 12: { 
                int pharmChoice;
                string pharmInput;
                
                while (true) {
                    printPharmacyMenu();
                    getline(cin, pharmInput);
                    
                    try {
                        pharmChoice = stoi(pharmInput);
                    } catch (...) {
                        pharmChoice = 0;
                    }
                    
                    switch (pharmChoice) {
                        case 1: { // Add a new pharmacy
                            string name, address, contact;
                            
                            cout << "Enter pharmacy name: ";
                            getline(cin, name);
                            if (name.empty()) {
                                cout << "Error: Pharmacy name cannot be empty.\n";
                                break;
                            }
                            
                            cout << "Enter pharmacy address (optional): ";
                            getline(cin, address);
                            
                            cout << "Enter pharmacy contact number (optional): ";
                            getline(cin, contact);
                            
                            pharmManager.addPharmacy(name, address, contact);
                            break;
                        }
                        case 2: { // Display all pharmacies
                            pharmManager.displayAllPharmacies();
                            break;
                        }
                        case 3: { // Deliver medicine
                            int pharmacyId, hospitalId;
                            double cost;
                            string medicine, temp;
                            
                            cout << "Enter pharmacy ID: ";
                            getline(cin, temp);
                            try {
                                pharmacyId = stoi(temp);
                            } catch (...) {
                                cout << "Error: Invalid pharmacy ID.\n";
                                break;
                            }
                            
                            cout << "Enter hospital ID: ";
                            getline(cin, temp);
                            try {
                                hospitalId = stoi(temp);
                            } catch (...) {
                                cout << "Error: Invalid hospital ID.\n";
                                break;
                            }
                            
                            cout << "Enter medicine name: ";
                            getline(cin, medicine);
                            if (medicine.empty()) {
                                cout << "Error: Medicine name cannot be empty.\n";
                                break;
                            }
                            
                            cout << "Enter cost: ";
                            getline(cin, temp);
                            try {
                                cost = stod(temp);
                            } catch (...) {
                                cout << "Error: Invalid cost.\n";
                                break;
                            }
                            
                            pharmManager.deliverMedicine(pharmacyId, hospitalId, medicine, cost);
                            break;
                        }
                        case 4: { // View hospital bill
                            int pharmacyId, hospitalId;
                            string temp;
                            
                            cout << "Enter pharmacy ID: ";
                            getline(cin, temp);
                            try {
                                pharmacyId = stoi(temp);
                            } catch (...) {
                                cout << "Error: Invalid pharmacy ID.\n";
                                break;
                            }
                            
                            cout << "Enter hospital ID: ";
                            getline(cin, temp);
                            try {
                                hospitalId = stoi(temp);
                            } catch (...) {
                                cout << "Error: Invalid hospital ID.\n";
                                break;
                            }
                            
                            double bill = pharmManager.getHospitalBill(pharmacyId, hospitalId);
                            cout << "Hospital #" << hospitalId << " owes $" << bill 
                                 << " to Pharmacy #" << pharmacyId << endl;
                            break;
                        }
                        case 5: { // Clear hospital bill
                            int pharmacyId, hospitalId;
                            string temp;
                            
                            cout << "Enter pharmacy ID: ";
                            getline(cin, temp);
                            try {
                                pharmacyId = stoi(temp);
                            } catch (...) {
                                cout << "Error: Invalid pharmacy ID.\n";
                                break;
                            }
                            
                            cout << "Enter hospital ID: ";
                            getline(cin, temp);
                            try {
                                hospitalId = stoi(temp);
                            } catch (...) {
                                cout << "Error: Invalid hospital ID.\n";
                                break;
                            }
                            
                            pharmManager.clearHospitalBill(pharmacyId, hospitalId);
                            break;
                        }
                        case 6: { // Return to main menu
                            goto main_menu;
                        }
                        default: {
                            cout << "Invalid choice. Please enter a number between 1 to 6.\n";
                            break;
                        }
                    }
                }
                main_menu:
                break;
            }
            case 13: { // Exit
                cout << "Exiting.\n";
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 to 10.\n";
                break;
            }
        }
    }

    return 0; 
}