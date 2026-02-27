#include "Brewer.h"

Brewer::Brewer(int id,
    const std::string& name,
    double price,
    int quantity,
    BrewerType brewerType,
    const std::string& material,
    int servings)
    : Product(id, name, price, quantity),
    brewerType(brewerType),
    material(material),
    servings(servings)
{
}

//wszystkie zaparzacze maj¹ kategoriê "Brewer"
std::string Brewer::getCategory() const {
    return "Brewer";
}

BrewerType Brewer::getBrewerType() const {
    return brewerType;
}

std::string Brewer::getMaterial() const {
    return material;
}

int Brewer::getServings() const {
    return servings;
}

std::string Brewer::getType() const {
    switch (brewerType) {
    case BrewerType::Dripper: return "Dripper";
    case BrewerType::FrenchPress: return "FrenchPress";
    case BrewerType::CoffeePot: return "CoffeePot";
    default: return "Unknown";
    }
}


