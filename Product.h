#pragma once
#include <string>

class Product {
protected:
    int id;
    std::string name;
    double price;
    int quantity;

public:
    Product(int id, const std::string& name, double price, int quantity);
    virtual ~Product() = default;

    virtual std::string getType() const = 0;
    virtual std::string getCategory() const = 0;

    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;

    void setId(int id);
    void setName(const std::string& name);
    void setPrice(double price);
    void setQuantity(int quantity);
};

