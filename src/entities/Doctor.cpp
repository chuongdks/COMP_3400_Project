#include <iostream>

// Doctor also has-a Patient. 
class Doctor {
    private:
    int id;
    std::string name;
    std::string role;
    std::string hospitalAdmitted;
    // Add Vector of Patients (Doctor treat multiple Patients)

    public: 
    Doctor(std::string name, std::string role)
        : name{ name }
        , role{ role }
    {}

    // Getter methods
    int getId() const {
        return id;
    }

    std::string getName() {
        return name;
    }    

    std::string getRole() {
        return role;
    }    

    // Setter methods
    void setId(int id) {
        this->id = id;
    }

};