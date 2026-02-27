#include "Coffee.h"

Coffee::Coffee(int id,
    const std::string& name,
    double price,
    int quantity,
    CoffeeForm coffeeForm,
    RoastLevel roastLevel,
    const std::string& originCountry,
    int weightGrams)
    : Product(id, name, price, quantity),
    coffeeForm(coffeeForm),
    roastLevel(roastLevel),
    originCountry(originCountry),
    weightGrams(weightGrams)
{
}

//wszystkie kawy maj¹ kategoriê "Coffee"
std::string Coffee::getCategory() const {
    return "Coffee";
}

RoastLevel Coffee::getRoastLevel() const {
    return roastLevel;
}

std::string Coffee::getOriginCountry() const {
    return originCountry;
}

int Coffee::getWeightGrams() const {
    return weightGrams;
}

CoffeeForm Coffee::getCoffeeForm() const {
    return coffeeForm;
}

std::string Coffee::getType() const {
    return (coffeeForm == CoffeeForm::Bean)
        ? "BeanCoffee"
        : "GroundCoffee";
}