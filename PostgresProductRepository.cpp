#include "PostgresProductRepository.h"
#include <pqxx/pqxx>
#include <stdexcept>
#include <iostream>

PostgresProductRepository::PostgresProductRepository(const std::string& connStr)
    : connectionString(connStr) {
}

void PostgresProductRepository::add(std::shared_ptr<Product> product) {
    try {
        pqxx::connection c(connectionString);
        pqxx::work txn(c);

        std::string sql;

        if (auto coffee = std::dynamic_pointer_cast<Coffee>(product)) {
            sql = "INSERT INTO products "
                "(name, price, quantity, category, coffee_form, roast_level, origin_country, weight_grams) "
                "VALUES (" +
                txn.quote(coffee->getName()) + "," +
                txn.quote(coffee->getPrice()) + "," +
                txn.quote(coffee->getQuantity()) + "," +
                txn.quote(coffee->getCategory()) + "," +
                txn.quote(coffeeFormToString(coffee->getCoffeeForm())) + "," +
                txn.quote(roastLevelToString(coffee->getRoastLevel())) + "," +
                txn.quote(coffee->getOriginCountry()) + "," +
                txn.quote(coffee->getWeightGrams()) + ") RETURNING id;";
        }
        else if (auto grinder = std::dynamic_pointer_cast<Grinder>(product)) {
            sql = "INSERT INTO products "
                "(name, price, quantity, category, grinder_type, burr_type, for_espresso) "
                "VALUES (" +
                txn.quote(grinder->getName()) + "," +
                txn.quote(grinder->getPrice()) + "," +
                txn.quote(grinder->getQuantity()) + "," +
                txn.quote(grinder->getCategory()) + "," +
                txn.quote(grinderTypeToString(grinder->getGrinderType())) + "," +
                txn.quote(burrTypeToString(grinder->getBurrType())) + "," +
                txn.quote(grinder->supportsEspresso()) + ") RETURNING id;";
        }
        else if (auto brewer = std::dynamic_pointer_cast<Brewer>(product)) {
            sql = "INSERT INTO products "
                "(name, price, quantity, category, brewer_type, material, servings) "
                "VALUES (" +
                txn.quote(brewer->getName()) + "," +
                txn.quote(brewer->getPrice()) + "," +
                txn.quote(brewer->getQuantity()) + "," +
                txn.quote(brewer->getCategory()) + "," +
                txn.quote(brewerTypeToString(brewer->getBrewerType())) + "," +
                txn.quote(brewer->getMaterial()) + "," +
                txn.quote(brewer->getServings()) + ") RETURNING id;";
        }
        else if (auto machine = std::dynamic_pointer_cast<CoffeeMachine>(product)) {
            sql = "INSERT INTO products "
                "(name, price, quantity, category, machine_type, power_watts, milk_frother, capacity_ml) "
                "VALUES (" +
                txn.quote(machine->getName()) + "," +
                txn.quote(machine->getPrice()) + "," +
                txn.quote(machine->getQuantity()) + "," +
                txn.quote(machine->getCategory()) + "," +
                txn.quote(machineTypeToString(machine->getTypeEnum())) + "," +
                txn.quote(machine->getPowerWatts()) + "," +
                txn.quote(machine->hasMilkFrother()) + "," +
                txn.quote(machine->getCapacityMl()) + ") RETURNING id;";
        }
        else {
            throw std::runtime_error("Nieznany typ produktu");
        }

        pqxx::result r = txn.exec(sql);
        txn.commit();

        product->setId(r[0][0].as<int>());

        std::cout << "Produkt dodany do bazy z ID: " << product->getId() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Blad przy dodawaniu produktu: " << e.what() << std::endl;
    }
}

std::vector<std::shared_ptr<Product>> PostgresProductRepository::getAll() const {
    std::vector<std::shared_ptr<Product>> products;

    try {
        pqxx::connection c(connectionString);
        pqxx::work txn(c);

        pqxx::result r = txn.exec("SELECT * FROM products;");

        for (const auto& row : r) {
            std::string category = row["category"].c_str();

            if (category == "Coffee") {
                auto coffee = std::make_shared<Coffee>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToCoffeeForm(row["coffee_form"].c_str()),
                    stringToRoastLevel(row["roast_level"].c_str()),
                    row["origin_country"].c_str(),
                    row["weight_grams"].as<int>()
                );
                products.push_back(coffee);
            }
            else if (category == "Grinder") {
                auto grinder = std::make_shared<Grinder>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToGrinderType(row["grinder_type"].c_str()),
                    stringToBurrType(row["burr_type"].c_str()),
                    row["for_espresso"].as<bool>()
                );
                products.push_back(grinder);
            }
            else if (category == "Brewer") {
                auto brewer = std::make_shared<Brewer>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToBrewerType(row["brewer_type"].c_str()),
                    row["material"].c_str(),
                    row["servings"].as<int>()
                );
                products.push_back(brewer);
            }
            else if (category == "CoffeeMachine") {
                auto machine = std::make_shared<CoffeeMachine>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToMachineType(row["machine_type"].c_str()),
                    row["power_watts"].as<int>(),
                    row["milk_frother"].as<bool>(),
                    row["capacity_ml"].as<int>()
                );
                products.push_back(machine);
            }
            else {
                std::cerr << "Nieznana kategoria w bazie: " << category << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Blad przy pobieraniu produktow: " << e.what() << std::endl;
    }

    return products;
}

void PostgresProductRepository::remove(int id) {
    try {
        pqxx::connection c(connectionString);
        pqxx::work txn(c);

        auto result = txn.exec("DELETE FROM products WHERE id = " + txn.quote(id) + ";");
        if (result.affected_rows() == 0) {
            std::cout << "Nie znaleziono produktu o ID " << id << std::endl;
        }

        txn.commit();
        std::cout << "Produkt o ID " << id << " usuniety z bazy." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Blad przy usuwaniu produktu: " << e.what() << std::endl;
    }
}

void PostgresProductRepository::update(int id, std::shared_ptr<Product> product) {
    try {
        pqxx::connection c(connectionString);
        pqxx::work txn(c);

        std::string sql;

        if (product->getCategory() == "Coffee") {
            auto coffee = std::dynamic_pointer_cast<Coffee>(product);
            sql = "UPDATE products SET "
                "name = " + txn.quote(coffee->getName()) + ", "
                "price = " + txn.quote(coffee->getPrice()) + ", "
                "quantity = " + txn.quote(coffee->getQuantity()) + ", "
                "coffee_form = " + txn.quote(coffeeFormToString(coffee->getCoffeeForm())) + ", "
                "roast_level = " + txn.quote(roastLevelToString(coffee->getRoastLevel())) + ", "
                "origin_country = " + txn.quote(coffee->getOriginCountry()) + ", "
                "weight_grams = " + txn.quote(coffee->getWeightGrams()) + " "
                "WHERE id = " + txn.quote(id) + ";";
        }
        else if (product->getCategory() == "Grinder") {
            auto grinder = std::dynamic_pointer_cast<Grinder>(product);
            sql = "UPDATE products SET "
                "name = " + txn.quote(grinder->getName()) + ", "
                "price = " + txn.quote(grinder->getPrice()) + ", "
                "quantity = " + txn.quote(grinder->getQuantity()) + ", "
                "grinder_type = " + txn.quote(grinderTypeToString(grinder->getGrinderType())) + ", "
                "burr_type = " + txn.quote(burrTypeToString(grinder->getBurrType())) + ", "
                "for_espresso = " + txn.quote(grinder->supportsEspresso()) + " "
                "WHERE id = " + txn.quote(id) + ";";
        }
        else if (product->getCategory() == "Brewer") {
            auto brewer = std::dynamic_pointer_cast<Brewer>(product);
            sql = "UPDATE products SET "
                "name = " + txn.quote(brewer->getName()) + ", "
                "price = " + txn.quote(brewer->getPrice()) + ", "
                "quantity = " + txn.quote(brewer->getQuantity()) + ", "
                "brewer_type = " + txn.quote(brewerTypeToString(brewer->getBrewerType())) + ", "
                "material = " + txn.quote(brewer->getMaterial()) + ", "
                "servings = " + txn.quote(brewer->getServings()) + " "
                "WHERE id = " + txn.quote(id) + ";";
        }
        else if (product->getCategory() == "CoffeeMachine") {
            auto machine = std::dynamic_pointer_cast<CoffeeMachine>(product);
            sql = "UPDATE products SET "
                "name = " + txn.quote(machine->getName()) + ", "
                "price = " + txn.quote(machine->getPrice()) + ", "
                "quantity = " + txn.quote(machine->getQuantity()) + ", "
                "machine_type = " + txn.quote(machineTypeToString(machine->getTypeEnum())) + ", "
                "power_watts = " + txn.quote(machine->getPowerWatts()) + ", "
                "milk_frother = " + txn.quote(machine->hasMilkFrother()) + ", "
                "capacity_ml = " + txn.quote(machine->getCapacityMl()) + " "
                "WHERE id = " + txn.quote(id) + ";";
        }
        else {
            std::cerr << "Nieznana kategoria produktu, nie mozna zaktualizowac." << std::endl;
            return;
        }

        auto result = txn.exec(sql);
        if (result.affected_rows() == 0) {
            std::cout << "Nie znaleziono produktu o ID " << id << " do aktualizacji.\n";
        }
        txn.commit();

        std::cout << "Produkt o ID " << id << " zaktualizowany w bazie." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Blad przy aktualizacji produktu: " << e.what() << std::endl;
    }
}

// Mapowanie enumów na string
std::string PostgresProductRepository::coffeeFormToString(CoffeeForm form) {
    switch (form) {
    case CoffeeForm::Bean: return "Bean";
    case CoffeeForm::Ground: return "Ground";
    }
    return "Unknown";
}

std::string PostgresProductRepository::roastLevelToString(RoastLevel level) {
    switch (level) {
    case RoastLevel::Light: return "Light";
    case RoastLevel::Medium: return "Medium";
    case RoastLevel::Dark: return "Dark";
    }
    return "Unknown";
}

std::string PostgresProductRepository::grinderTypeToString(GrinderType type) {
    switch (type) {
    case GrinderType::Hand: return "Hand";
    case GrinderType::Automatic: return "Automatic";
    }
    return "Unknown";
}

std::string PostgresProductRepository::burrTypeToString(BurrType type) {
    switch (type) {
    case BurrType::Conical: return "Conical";
    case BurrType::Flat: return "Flat";
    }
    return "Unknown";
}

std::string PostgresProductRepository::brewerTypeToString(BrewerType type) {
    switch (type) {
    case BrewerType::Dripper: return "Dripper";
    case BrewerType::FrenchPress: return "FrenchPress";
    case BrewerType::CoffeePot: return "CoffeePot";
    }
    return "Unknown";
}

std::string PostgresProductRepository::machineTypeToString(CoffeeMachineType type) {
    switch (type) {
    case CoffeeMachineType::PourOver: return "PourOver";
    case CoffeeMachineType::Piston: return "Piston";
    case CoffeeMachineType::Automatic: return "Automatic";
    }
    return "Unknown";
}

// Mapowanie string na enum
CoffeeForm PostgresProductRepository::stringToCoffeeForm(const std::string& str) {
    if (str == "Bean") return CoffeeForm::Bean;
    if (str == "Ground") return CoffeeForm::Ground;
    return CoffeeForm::Bean;
}

RoastLevel PostgresProductRepository::stringToRoastLevel(const std::string& str) {
    if (str == "Light") return RoastLevel::Light;
    if (str == "Medium") return RoastLevel::Medium;
    if (str == "Dark") return RoastLevel::Dark;
    return RoastLevel::Medium;
}

GrinderType PostgresProductRepository::stringToGrinderType(const std::string& str) {
    if (str == "Hand") return GrinderType::Hand;
    if (str == "Automatic") return GrinderType::Automatic;
    return GrinderType::Hand;
}

BurrType PostgresProductRepository::stringToBurrType(const std::string& str) {
    if (str == "Conical") return BurrType::Conical;
    if (str == "Flat") return BurrType::Flat;
    return BurrType::Conical;
}

BrewerType PostgresProductRepository::stringToBrewerType(const std::string& str) {
    if (str == "Dripper") return BrewerType::Dripper;
    if (str == "FrenchPress") return BrewerType::FrenchPress;
    if (str == "CoffeePot") return BrewerType::CoffeePot;
    return BrewerType::Dripper;
}

CoffeeMachineType PostgresProductRepository::stringToMachineType(const std::string& str) {
    if (str == "PourOver") return CoffeeMachineType::PourOver;
    if (str == "Piston") return CoffeeMachineType::Piston;
    if (str == "Automatic") return CoffeeMachineType::Automatic;
    return CoffeeMachineType::PourOver;
}

PriceStats PostgresProductRepository::getPriceStats(ProductCategory category) const {
    pqxx::connection conn(connectionString);
    pqxx::work txn(conn);

    std::string sql =
        "SELECT MIN(price), MAX(price), AVG(price) FROM products";

    if (category != ProductCategory::All) {
        sql += " WHERE category = " + txn.quote(toString(category));
    }

    pqxx::result r = txn.exec(sql);
    pqxx::row row = r.one_row();

    PriceStats stats;
    stats.min = row[0].is_null() ? 0.0 : row[0].as<double>();
    stats.max = row[1].is_null() ? 0.0 : row[1].as<double>();
    stats.avg = row[2].is_null() ? 0.0 : row[2].as<double>();

    return stats;
}

std::vector<std::shared_ptr<Product>>
PostgresProductRepository::getSorted(
    SortField field,
    SortOrder order,
    ProductCategory category
) const {
    std::vector<std::shared_ptr<Product>> products;

    try {
        pqxx::connection conn(connectionString);
        pqxx::work txn(conn);

        std::string sql = "SELECT * FROM products";

        if (category != ProductCategory::All) {
            sql += " WHERE category = " + txn.quote(toString(category));
        }

        switch (field) {
        case SortField::Id:    sql += " ORDER BY id"; break;
        case SortField::Price: sql += " ORDER BY price"; break;
        }

        if (order == SortOrder::Desc) {
            sql += " DESC";
        }
        else {
            sql += " ASC";
        }

        sql += ";";

        pqxx::result r = txn.exec(sql);

        for (const auto& row : r) {
            std::string cat = row["category"].c_str();

            if (cat == "Coffee") {
                auto coffee = std::make_shared<Coffee>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToCoffeeForm(row["coffee_form"].c_str()),
                    stringToRoastLevel(row["roast_level"].c_str()),
                    row["origin_country"].c_str(),
                    row["weight_grams"].as<int>()
                );
                products.push_back(coffee);
            }
            else if (cat == "Grinder") {
                auto grinder = std::make_shared<Grinder>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToGrinderType(row["grinder_type"].c_str()),
                    stringToBurrType(row["burr_type"].c_str()),
                    row["for_espresso"].as<bool>()
                );
                products.push_back(grinder);
            }
            else if (cat == "Brewer") {
                auto brewer = std::make_shared<Brewer>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToBrewerType(row["brewer_type"].c_str()),
                    row["material"].c_str(),
                    row["servings"].as<int>()
                );
                products.push_back(brewer);
            }
            else if (cat == "CoffeeMachine") {
                auto machine = std::make_shared<CoffeeMachine>(
                    row["id"].as<int>(),
                    row["name"].c_str(),
                    row["price"].as<double>(),
                    row["quantity"].as<int>(),
                    stringToMachineType(row["machine_type"].c_str()),
                    row["power_watts"].as<int>(),
                    row["milk_frother"].as<bool>(),
                    row["capacity_ml"].as<int>()
                );
                products.push_back(machine);
            }
            else {
                std::cerr << "Nieznana kategoria w bazie: " << cat << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Blad przy pobieraniu posortowanych produktow: " << e.what() << std::endl;
    }

    return products;
}





