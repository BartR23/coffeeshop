#pragma once

#include <vector>
#include <memory>
#include <string>

#include "IProductRepository.h"
#include "Product.h"
#include "Coffee.h"
#include "Grinder.h"
#include "Brewer.h"
#include "CoffeeMachine.h"
#include "PriceStats.h"
#include "ProductCategory.h"
#include "Sort.h"

class PostgresProductRepository : public IProductRepository {
private:
    std::string connectionString;   

public:
    explicit PostgresProductRepository(const std::string& connStr);
    ~PostgresProductRepository() override = default;

    void add(std::shared_ptr<Product> product) override;
    std::vector<std::shared_ptr<Product>> getAll() const override;
    void remove(int id) override;
    void update(int id, std::shared_ptr<Product> product) override;

    PriceStats getPriceStats(ProductCategory category) const override;

    std::vector<std::shared_ptr<Product>> getSorted(
        SortField field,
        SortOrder order,
        ProductCategory category
    ) const override;

private:
    // Funkcje pomocnicze do mapowania enumów na tekst
    static std::string coffeeFormToString(CoffeeForm form);
    static std::string roastLevelToString(RoastLevel level);
    static std::string grinderTypeToString(GrinderType type);
    static std::string burrTypeToString(BurrType type);
    static std::string brewerTypeToString(BrewerType type);
    static std::string machineTypeToString(CoffeeMachineType type);

    // Funkcje pomocnicze do mapowania tekstu na enumy
    static CoffeeForm stringToCoffeeForm(const std::string& str);
    static RoastLevel stringToRoastLevel(const std::string& str);
    static GrinderType stringToGrinderType(const std::string& str);
    static BurrType stringToBurrType(const std::string& str);
    static BrewerType stringToBrewerType(const std::string& str);
    static CoffeeMachineType stringToMachineType(const std::string& str);
};
