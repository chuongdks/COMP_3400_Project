#include <iostream>
#include "Hospital.cpp"
#include "Pharmacy.cpp"

int main() {
    Hospital h1(1, "City Hospital");
    Doctor d1(101, "Dr. Smith", "Cardiology");
    Nurse n1(201, "Nurse Alice");
    Patient p1(301, "John Doe", "Flu");
    Pharmacy ph1(401, "MedCare Pharmacy");

    h1.assignDoctor(&d1);
    h1.assignNurse(&n1);
    h1.admitPatient(&p1);

    p1.updateDays(3);
    std::cout << "Bill for " << p1.getName() << ": $" << p1.getBill();

    ph1.deliverMedicine();
    
    h1.displayHospitalInfo();
    h1.dischargePatient(301);

    // **Copy Constructor**
    std::cout << "\nCreating h2 using Copy Constructor from h1...\n";
    Hospital h2 = h1;  // Calls Copy Constructor
    h2.displayHospitalInfo();

    // **Copy Assignment**
    std::cout << "\nCreating h5 using Copy Assignment from h1...\n";
    Hospital h5(2, "Another Hospital");
    h5 = h1;  // **Copy assignment happens here**
    h5.displayHospitalInfo();

    // **Move Constructor**
    std::cout << "\nCreating h3 using Move Constructor from h1...\n";
    Hospital h3 = std::move(h1);  // Calls Move Constructor
    h3.displayHospitalInfo();

    // **Move Assignment**
    std::cout << "\nAssigning h2 to h4 using Move Assignment...\n";
    Hospital h4(4, "Temporary Hospital");
    h4 = std::move(h2);  // Calls Move Assignment Operator
    h4.displayHospitalInfo();

    return 0;
}

