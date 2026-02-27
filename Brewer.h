#pragma once
#include "Product.h"
#include <string>

enum class BrewerType {
    Dripper,
    FrenchPress,
    CoffeePot
};


class Brewer : public Product {
protected:
    std::string material;  
    int servings;          
    BrewerType brewerType;


public:
    Brewer(int id,
        const std::string& name,
        double price,
        int quantity,
        BrewerType brewerType,
        const std::string& material,
        int servings);


    std::string getCategory() const override;
    BrewerType getBrewerType() const;
    std::string getType() const override;

    std::string getMaterial() const;
    int getServings() const;

};


