#include <iostream>

class Pharmacy {
    private:
    int id;
    std::string name;

    public:
    Pharmacy(int id, std::string name)
        : id{ id }
        , name{ name }
    {}

    void deliverMedicine() {
        // do something here
        std::cout << "Medicine is delivered from Pharma " << name << std::endl;
    }
};