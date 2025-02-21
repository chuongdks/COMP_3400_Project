#include <iostream>

class Nurse {
    private:
    int id;
    std::string name;
    std::string hospitalAdmitted;
    // Add Vector of Patients (Nurse treat max of 2 Patients)

    public:
    Nurse(std::string name)
        : name{ name }
    {}

    // Getter methods
    int getId() const {
        return id;
    }

    std::string getName() {
        return name;
    }    

    // Setter methods
    void setId(int id) {
        this->id = id;
    }
};