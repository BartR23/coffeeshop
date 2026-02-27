#pragma once

#include <vector>
#include <memory>

#include "Product.h"
#include "PriceStats.h"
#include "ProductCategory.h"
#include "Sort.h"

class IProductRepository {
public:
    virtual ~IProductRepository() = default;

    // CREATE
    virtual void add(std::shared_ptr<Product> product) = 0;

    // READ
    virtual std::vector<std::shared_ptr<Product>> getAll() const = 0;

    // DELETE
    virtual void remove(int id) = 0;

    //UPDATE
    virtual void update(int id, std::shared_ptr<Product> product) = 0;

    //STATISTICS
    virtual PriceStats getPriceStats(ProductCategory category) const = 0;

    //SORTING
    virtual std::vector<std::shared_ptr<Product>> getSorted(
        SortField field,
        SortOrder order,
        ProductCategory category
    ) const = 0;
};