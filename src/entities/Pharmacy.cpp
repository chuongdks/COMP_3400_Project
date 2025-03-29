#ifndef PHARMACY_CPP
#define PHARMACY_CPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Pharmacy {
    private:
    int id;
    std::string name;
    std::string address;
    std::string contactNumber;
    // Map to store bills for different hospitals
    std::map<int, double> hospitalBills; // hospital_id -> bill_amount

    public:
    // Constructor
    Pharmacy(int id, std::string name)
        : id{ id }
        , name{ name }
    {}
    
    // Constructor with additional data
    Pharmacy(int id, std::string name, std::string address, std::string contactNumber)
        : id{ id }
        , name{ name }
        , address{ address }
        , contactNumber{ contactNumber }
    {}

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getContactNumber() const { return contactNumber; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setAddress(std::string address) { this->address = address; }
    void setContactNumber(std::string contact) { this->contactNumber = contact; }

    // Billing methods
    void billHospital(int hospitalId, double amount) {
        if (hospitalBills.find(hospitalId) != hospitalBills.end()) {
            hospitalBills[hospitalId] += amount;
        } else {
            hospitalBills[hospitalId] = amount;
        }
        std::cout << "Billed hospital #" << hospitalId 
                  << " for $" << amount 
                  << " from pharmacy " << name << std::endl;
    }
    
    double getHospitalBill(int hospitalId) const {
        auto it = hospitalBills.find(hospitalId);
        if (it != hospitalBills.end()) {
            return it->second;
        }
        return 0.0; // No bill found for this hospital
    }
    
    void clearHospitalBill(int hospitalId) {
        hospitalBills[hospitalId] = 0.0;
        std::cout << "Cleared bill for hospital #" << hospitalId << std::endl;
    }
    
    // Display all hospital bills
    void displayAllBills() const {
        std::cout << "Bills for pharmacy " << name << " (ID: " << id << "):" << std::endl;
        if (hospitalBills.empty()) {
            std::cout << "No bills to display." << std::endl;
            return;
        }
        
        for (const auto& bill : hospitalBills) {
            std::cout << "Hospital #" << bill.first << ": $" << bill.second << std::endl;
        }
    }

    // Medicine delivery function
    void deliverMedicine(int hospitalId, const std::string& medicine, double cost) {
        billHospital(hospitalId, cost);
        std::cout << "Medicine '" << medicine << "' delivered to hospital #" 
                  << hospitalId << " from pharmacy " << name << std::endl;
    }
    
    // Simple delivery method
    void deliverMedicine() {
        std::cout << "Medicine is delivered from Pharmacy " << name << std::endl;
    }
};

#endif