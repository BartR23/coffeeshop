#pragma once
#include "Product.h"
#include <string>

enum class GrinderType {
    Hand,
    Automatic
};

enum class BurrType {
    Conical,
    Flat
};

class Grinder : public Product {
protected:
    GrinderType grinderType;   // Hand / Automatic
    BurrType burrType;
    bool forEspresso;

public:
    Grinder(int id,
        const std::string& name,
        double price,
        int quantity,
        GrinderType grinderType,
        BurrType burrType,
        bool forEspresso);

    std::string getCategory() const override;
    std::string getType() const override;

    BurrType getBurrType() const;
    bool supportsEspresso() const;
    GrinderType getGrinderType() const;
    
};