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
    std::cout << "Bill for " << p1.getName() << ": $" << p1.getBill() << std::endl;

    ph1.deliverMedicine();
    
    h1.displayHospitalInfo();
    h1.dischargePatient(301);

    return 0;
}

