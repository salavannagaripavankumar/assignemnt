#include <iostream>
#include <string>
using namespace std;

// Class representing Small Molecule Functionalities
class SMF {
private:
    std::string name;
    double propertyValue;

public:
    SMF(const std::string& n, double val) : name(n), propertyValue(val) {}

    void display() const {
        std::cout << "SMF Name: " << name << ", Property Value: " << propertyValue << std::endl;
    }

    double getProperty() const {
        return propertyValue;
    }

    void setProperty(double val) {
        propertyValue = val;
    }
};

// Class representing User-Provided Functions
class UPF {
public:
    // Method to interact with SMF and modify its property
    void modifySMF(SMF& smf, double newValue) const {
        smf.setProperty(newValue);
        std::cout << "SMF property modified to: " << newValue << std::endl;
    }

    // Method to perform a calculation using SMF's property
    double calculateWithSMF(const SMF& smf) const {
        double result = smf.getProperty() * 2; // Example calculation
        std::cout << "Calculated result with SMF property: " << result << std::endl;
        return result;
    }
};

int main() {
    // Create an instance of SMF
    SMF mySMF("ExampleSMF", 5.0);
    mySMF.display();

    // Create an instance of UPF
    UPF myUPF;

    // Interact with SMF using UPF
    myUPF.modifySMF(mySMF, 10.0);
    mySMF.display();

    // Perform calculation using UPF and SMF
    double result = myUPF.calculateWithSMF(mySMF);
    std::cout << "Final result: " << result << std::endl;

    return 0;
}
