#pragma once
#include "Product.h"
#include "Coffee.h"
#include "Grinder.h"
#include "Brewer.h"
#include "CoffeeMachine.h"
#include <memory>
#include <iostream>
#include <string>
#include <vector>

class ProductFactory {
public:
    static std::shared_ptr<Product> createProduct();
};

//Szablon chooseEnum
template<typename T>
T chooseEnum(const std::string& prompt, const std::vector<std::pair<std::string, T>>& options) {
    std::cout << prompt << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i].first << std::endl;
    }

    int choice = 0;
    std::cin >> choice;
    while (choice < 1 || choice > static_cast<int>(options.size())) {
        std::cout << "Nieprawid³owy wybór, spróbuj ponownie: ";
        std::cin >> choice;
    }
    return options[choice - 1].second;
}
