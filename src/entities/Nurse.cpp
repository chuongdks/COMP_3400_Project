#include <iostream>

class Nurse {
    private:
    int id;
    std::string name;

    public:
    Nurse(int id, std::string name)
        : id{ id }
        , name{ name }
    {}

    // Getter methods
    int getID() const {
        return id;
    }

    std::string getName() {
        return name;
    }    

    // Setter methods
};