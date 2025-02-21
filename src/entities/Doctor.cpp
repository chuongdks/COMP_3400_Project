#include <iostream>

// Doctor also has-a Patient. 
class Doctor {
    private:
    int id;
    std::string name;
    std::string role;
    std::string hospitalAdmitted;
    // Add Vector of Patients (Doctor treat ultiple Patients)

    public: 
    Doctor(int id, std::string name, std::string role)
        : id{ id }
        , name{ name }
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
    
};