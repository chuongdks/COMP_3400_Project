#include <iostream>
#include "Hospital.cpp"
#include "./entities/Pharmacy.cpp"
#include "./database/Database.cpp"

int main() {
    // Hospital h1(1, "City Hospital");
    // Doctor d1(101, "Dr. Smith", "Cardiology");
    // Nurse n1(201, "Nurse Alice");
    // Patient p1(301, "John Doe", "Flu", 50, 0);
    // Pharmacy ph1(401, "MedCare Pharmacy");

    // h1.assignDoctor(&d1);
    // h1.assignNurse(&n1);
    // h1.admitPatient(&p1);

    // p1.updateDays(3);
    // std::cout << "Bill for " << p1.getName() << ": $" << p1.getBill();

    // ph1.deliverMedicine();
    
    // h1.displayHospitalInfo();
    // h1.dischargePatient(301);

    // // **Copy Constructor**
    // std::cout << "\nCreating h2 using Copy Constructor from h1...\n";
    // Hospital h2 = h1;  // Calls Copy Constructor
    // h2.displayHospitalInfo();

    // // **Copy Assignment**
    // std::cout << "\nCreating h5 using Copy Assignment from h1...\n";
    // Hospital h5(2, "Another Hospital");
    // h5 = h1;  // **Copy assignment happens here**
    // h5.displayHospitalInfo();

    // // **Move Constructor**
    // std::cout << "\nCreating h3 using Move Constructor from h1...\n";
    // Hospital h3 = std::move(h1);  // Calls Move Constructor
    // h3.displayHospitalInfo();

    // // **Move Assignment**
    // std::cout << "\nAssigning h2 to h4 using Move Assignment...\n";
    // Hospital h4(4, "Temporary Hospital");
    // h4 = std::move(h2);  // Calls Move Assignment Operator
    // h4.displayHospitalInfo();

    // Create and Initialize the Database and table 
    const char* dbPath = "../db/hospital.db";
    Database db(dbPath);
    db.createDB();
    db.createTable();

    // Example: Insert a patient
    // db.executeSQL("INSERT INTO Patient (id, name, disease, bill, daysInHospital) VALUES (1, 'John Doe', 'Flu', 50, 0);");

    Hospital h1("City Hospital", db);
    h1.displayHospitalInfo();
    Hospital h2("Town Hospital", db);
    h2.displayHospitalInfo();
    Hospital h3("Dirty Hospital", db);
    h3.displayHospitalInfo();

    Patient p1("John Doe", "Flu", 50, 0);

    return 0;
}

