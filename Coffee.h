#pragma once
#include "Product.h"
#include <string>

enum class RoastLevel {
    Light,
    Medium,
    Dark
};

enum class CoffeeForm {
    Bean,     
    Ground    
};

class Coffee : public Product {
protected:
    CoffeeForm coffeeForm;       // ziarnista / mielona
    RoastLevel roastLevel;
    std::string originCountry;
    int weightGrams;


public:
    Coffee(int id,
        const std::string& name,
        double price,
        int quantity,
        CoffeeForm coffeeForm,
        RoastLevel roastLevel,
        const std::string& originCountry,
        int weightGrams);

    std::string getCategory() const override;

    RoastLevel getRoastLevel() const;
    std::string getOriginCountry() const;
    CoffeeForm getCoffeeForm() const;
    int getWeightGrams() const;
    std::string getType() const override;
};