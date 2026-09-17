#pragma once
#include <string>
#include <iostream>

class RobotBattery {
    private: 
        std::string batteryType;
        int chargeLevel;

    public:
        RobotBattery(const std::string& type, int initialCharge);
        void charge(int amount);
        void discharge(int amount);
        int getChargeLevel() const;
};

/*
take home message:
- header files should contain class declarations, member function prototypes, and necessary includes.
- & means pass by reference, which avoids copying the object and can improve performance. Other types of passes:
    - pass by value: creates a copy of the object, which can be inefficient for large objects.
    - pass by pointer: allows modification of the original object, but requires careful memory management.
    - pass by const reference: allows read-only access to the original object without copying it, which is efficient and safe.
    - pass by rvalue reference: allows moving resources from temporary objects, which can improve performance in certain scenarios.
 */