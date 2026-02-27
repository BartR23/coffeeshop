#include "ProductFactory.h"

// Tworzenie produktu
std::shared_ptr<Product> ProductFactory::createProduct() {
    std::cout << "Wybierz typ produktu:\n";
    std::cout << "1. Coffee\n2. Grinder\n3. Brewer\n4. CoffeeMachine\n";
    int typeChoice;
    std::cin >> typeChoice;
    std::cin.ignore();

    std::string name;
    double price;
    int quantity;

    std::cout << "Nazwa: ";
    std::getline(std::cin, name);
    std::cout << "Cena: ";
    std::cin >> price;
    std::cout << "Ilosc: ";
    std::cin >> quantity;

    switch (typeChoice) {
    case 1: { // Coffee
        RoastLevel roast = chooseEnum<RoastLevel>("Poziom palenia:",
            { {"Light", RoastLevel::Light}, {"Medium", RoastLevel::Medium}, {"Dark", RoastLevel::Dark} });

        std::string origin;
        std::cout << "Kraj pochodzenia: ";
        std::cin.ignore();
        std::getline(std::cin, origin);
        
        int weight;
        std::cout << "Waga w gramach: ";
        std::cin >> weight;

        CoffeeForm form = chooseEnum<CoffeeForm>("Forma kawy:",
            { {"Bean", CoffeeForm::Bean}, {"Ground", CoffeeForm::Ground} });

        auto coffee = std::make_shared<Coffee>(
            0,           // tymczasowe id
            name,         
            price,        
            quantity,     
            form,         
            roast,        
            origin,       
            weight        
        );

        return coffee;
    }

    case 2: { // Grinder
        GrinderType grinderType = chooseEnum<GrinderType>("Typ mlynka:",
            { {"Hand", GrinderType::Hand}, {"Automatic", GrinderType::Automatic} });

        BurrType burrType = chooseEnum<BurrType>("Typ zarna:",
            { {"Conical", BurrType::Conical}, {"Flat", BurrType::Flat} });

        bool forEspresso;
        char espressoInput;
        std::cout << "Czy mlynek obsluguje espresso? (y/n): ";
        std::cin >> espressoInput;
        forEspresso = (espressoInput == 'y' || espressoInput == 'Y');

        auto grinder = std::make_shared<Grinder>(
            0,             // tymczasowe id
            name,          
            price,        
            quantity,      
            grinderType,   
            burrType,      
            forEspresso   
        );

        return grinder;
    }

    case 3: { // Brewer
        BrewerType brewerType = chooseEnum<BrewerType>("Typ zaparzacza:",
            { {"Dripper", BrewerType::Dripper},
              {"FrenchPress", BrewerType::FrenchPress},
              {"CoffeePot", BrewerType::CoffeePot} });

        std::string material;
        std::cout << "Material wykonania: ";
        std::cin.ignore(); 
        std::getline(std::cin, material);

        int servings;
        std::cout << "Liczba porcji (filizanek): ";
        std::cin >> servings;

        auto brewer = std::make_shared<Brewer>(
            0,           // tymczasowe id
            name,        
            price,      
            quantity,    
            brewerType,  
            material,    
            servings     
        );

        return brewer;
    }

    case 4: { // CoffeeMachine
        CoffeeMachineType type = chooseEnum<CoffeeMachineType>("Typ ekspresu:",
            { {"PourOver", CoffeeMachineType::PourOver},
              {"Piston", CoffeeMachineType::Piston},
              {"Automatic", CoffeeMachineType::Automatic} });

        int power;
        std::cout << "Moc (W): ";
        std::cin >> power;

        bool milkFrother = false;
        int capacity = 0;

        if (type == CoffeeMachineType::PourOver) {
            std::cout << "Pojemnosc dzbanka (ml): ";
            std::cin >> capacity;
        }
        else {
            char milkInput;
            std::cout << "Czy ekspres moze przygotowywac napoje mleczne? (y/n): ";
            std::cin >> milkInput;
            milkFrother = (milkInput == 'y' || milkInput == 'Y');
        }

        auto machine = std::make_shared<CoffeeMachine>(
            0,            // tymczasowe id
            name,         
            price,        
            quantity,     
            type,         
            power,       
            milkFrother,  
            capacity      
        );

        return machine;
    }

    default:
        std::cout << "Nieprawidlowy wybor\n";
        return nullptr;
    }
}