#include <vector>
#include "Hospital.cpp"

// Manage the Hospital class
class HospitalManager {
    private:
        std::vector<Hospital*> hospitals;
        static const int MAX_HOSPITALS = 5;
        Database& db;


};
