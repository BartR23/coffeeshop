#include "Product.h"

Product::Product(int id, const std::string& name, double price, int quantity)
    : id(id), name(name), price(price), quantity(quantity)
{
}

int Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setId(int id) {
    this->id = id;
}

void Product::setName(const std::string& newName) {
    name = newName;
}

void Product::setPrice(double newPrice) {
    price = newPrice;
}

void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
