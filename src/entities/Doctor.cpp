#include <iostream>

class Doctor {
    private:
    int id;
    std::string name;
    std::string role;

    public: 
    Doctor(int id, std::string name, std::string role)
        : id{ id }
        , name{ name }
        , role{ role }
    {}

    // Getter methods
    int getID() const {
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