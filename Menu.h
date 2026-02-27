#pragma once
#include "IProductRepository.h"
#include "ProductFactory.h"
#include <memory>
#include <iostream>

class Menu {
private:
    IProductRepository& repo;

    void addProduct();
    void showProducts();
    void removeProduct();
    void updateProduct();

    void showSortedProducts();
    void showPriceStats();

    ProductCategory selectCategory() const;
    SortField selectSortField() const;
    SortOrder selectSortOrder() const;

public:
    Menu(IProductRepository& repository) : repo(repository) {}
    void run();
};