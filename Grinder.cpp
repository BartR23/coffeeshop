#include "Grinder.h"

Grinder::Grinder(int id,
    const std::string& name,
    double price,
    int quantity,
    GrinderType grinderType,
    BurrType burrType,
    bool forEspresso)
    : Product(id, name, price, quantity),
    grinderType(grinderType),
    burrType(burrType),
    forEspresso(forEspresso)
{
}

//wszystkie m³ynki maj¹ kategoriê "Grinder"
std::string Grinder::getCategory() const {
    return "Grinder";
}

BurrType Grinder::getBurrType() const {
    return burrType;
}

bool Grinder::supportsEspresso() const {
    return forEspresso;
}

std::string Grinder::getType() const {
    return (grinderType == GrinderType::Hand)
        ? "HandGrinder"
        : "AutomaticGrinder";
}

GrinderType Grinder::getGrinderType() const {
    return grinderType;
}

