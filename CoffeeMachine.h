#pragma once
#include "Product.h"
#include <string>

enum class CoffeeMachineType {
    PourOver,
    Piston,
    Automatic
};


class CoffeeMachine : public Product {
protected:
    CoffeeMachineType type;  
    int powerWatts;          
    // pola zale¿ne od typu:
    bool milkFrother;        // dla Piston i Automatic
    int capacityMl;          // dla PourOver


public:
    CoffeeMachine(int id,
        const std::string& name,
        double price,
        int quantity,
        CoffeeMachineType type,
        int powerWatts,
        bool milkFrother = false,
        int capacityMl = 0);


    std::string getCategory() const override;
    std::string getType() const override;

    CoffeeMachineType getTypeEnum() const;
    int getPowerWatts() const;

    bool hasMilkFrother() const; // tylko dla nie-PourOver
    int getCapacityMl() const;    // tylko dla PourOver

};



