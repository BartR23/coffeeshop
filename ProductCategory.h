#pragma once
#include <string>

enum class ProductCategory {
    All,
    Coffee,
    Grinder,
    Brewer,
    CoffeeMachine
};

inline std::string toString(ProductCategory c) {
    switch (c) {
    case ProductCategory::Coffee: return "Coffee";
    case ProductCategory::Grinder: return "Grinder";
    case ProductCategory::Brewer: return "Brewer";
    case ProductCategory::CoffeeMachine: return "CoffeeMachine";
    default: return "";
    }
}

