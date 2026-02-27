#include "CoffeeMachine.h"

CoffeeMachine::CoffeeMachine(int id,
    const std::string& name,
    double price,
    int quantity,
    CoffeeMachineType type,
    int powerWatts,
    bool milkFrother,
    int capacityMl)
    : Product(id, name, price, quantity),
    type(type),
    powerWatts(powerWatts),
    milkFrother(false),
    capacityMl(0)
{
    if (type == CoffeeMachineType::PourOver) {
        this->capacityMl = capacityMl;
    }
    else {
        this->milkFrother = milkFrother;
    }
}

//wszystkie ekspresy maj¹ kategoriê "CoffeeMachine"
std::string CoffeeMachine::getCategory() const {
    return "CoffeeMachine";
}
 
CoffeeMachineType CoffeeMachine::getTypeEnum() const {
    return type;
}

int CoffeeMachine::getPowerWatts() const {
    return powerWatts;
}

bool CoffeeMachine::hasMilkFrother() const {
    return milkFrother;
}

int CoffeeMachine::getCapacityMl() const {
    return capacityMl;
}

std::string CoffeeMachine::getType() const {
    switch (type) {
    case CoffeeMachineType::PourOver:  return "PourOver";
    case CoffeeMachineType::Piston:    return "Piston";
    case CoffeeMachineType::Automatic: return "Automatic";
    default: return "Unknown";
    }
}


