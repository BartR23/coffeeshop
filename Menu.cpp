#include "Menu.h"
#include "ProductFactory.h"
#include <iostream>
#include "Coffee.h"
#include "Grinder.h"
#include "Brewer.h"
#include "CoffeeMachine.h"

void Menu::run() {
    int choice = 0;

    do {
        std::cout << "\n=== Menu Coffeeshop ===\n";
        std::cout << "1. Dodaj produkt\n";
        std::cout << "2. Wyswietl produkty\n";
        std::cout << "3. Usun produkt\n";
        std::cout << "4. Aktualizuj produkt\n";
        std::cout << "5. Wyswietl produkty posortowane\n";
        std::cout << "6. Pokaz statystyki cenowe\n";
        std::cout << "0. Wyjscie\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> choice;

        switch (choice) {
        case 1: addProduct(); break;
        case 2: showProducts(); break;
        case 3: removeProduct(); break;
        case 4: updateProduct(); break;
        case 5: showSortedProducts(); break;
        case 6: showPriceStats(); break;
        case 0: std::cout << "Koniec programu.\n"; break;
        default: std::cout << "Nieprawidlowa opcja!\n"; break;
        }
    } while (choice != 0);
}

void Menu::addProduct() {
    auto product = ProductFactory::createProduct();
    if (product) {
        repo.add(product);
        std::cout << "Produkt dodany.\n";
    }
}

void Menu::showProducts() {
    auto products = repo.getAll();
    if (products.empty()) {
        std::cout << "Brak produktow w bazie.\n";
        return;
    }

    for (const auto& p : products) {
        std::cout << "ID: " << p->getId()
            << " | Nazwa: " << p->getName()
            << " | Cena: " << p->getPrice()
            << " | Ilosc: " << p->getQuantity()
            << " | Kategoria: " << p->getCategory()
            << " | Typ: " << p->getType()
            << "\n";
    }
}

void Menu::removeProduct() {
    int id;
    std::cout << "Podaj ID produktu do usuniecia: ";
    std::cin >> id;
    repo.remove(id);
    std::cout << "Produkt usuniety (jesli istnial).\n";
}

void Menu::updateProduct() {
    int id;
    std::cout << "Podaj ID produktu do aktualizacji: ";
    std::cin >> id;

    auto updated = ProductFactory::createProduct();
    if (updated) {
        repo.update(id, updated);
        std::cout << "Produkt zaktualizowany.\n";
    }
}

void Menu::showSortedProducts() {
    ProductCategory category = selectCategory();
    SortField field = selectSortField();
    SortOrder order = selectSortOrder();

    auto products = repo.getSorted(field, order, category);

    if (products.empty()) {
        std::cout << "Brak produktow w bazie dla wybranej kategorii.\n";
        return;
    }

    for (const auto& p : products) {
        std::cout << "ID: " << p->getId()
            << " | Nazwa: " << p->getName()
            << " | Cena: " << p->getPrice()
            << " | Ilosc: " << p->getQuantity()
            << " | Kategoria: " << p->getCategory()
            << " | Typ: " << p->getType()
            << "\n";
    }
}

void Menu::showPriceStats() {
    ProductCategory category = selectCategory();
    PriceStats stats = repo.getPriceStats(category);

    std::cout << "Statystyki cenowe dla kategorii: " << toString(category) << "\n";
    std::cout << "Min: " << stats.min << " | Max: " << stats.max << " | Srednia: " << stats.avg << "\n";

    std::cout << "\nProdukty z najnizsza cena:\n";
    auto products = repo.getSorted(SortField::Price, SortOrder::Asc, category);
    for (const auto& p : products) {
        if (p->getPrice() == stats.min) {
            std::cout << "ID: " << p->getId()
                << " | Nazwa: " << p->getName()
                << " | Cena: " << p->getPrice()
                << " | Ilosc: " << p->getQuantity()
                << " | Kategoria: " << p->getCategory()
                << " | Typ: " << p->getType()
                << "\n";
        }
        else break;
    }

    std::cout << "\nProdukty z najwyzsza cena:\n";
    products = repo.getSorted(SortField::Price, SortOrder::Desc, category);
    for (const auto& p : products) {
        if (p->getPrice() == stats.max) {
            std::cout << "ID: " << p->getId()
                << " | Nazwa: " << p->getName()
                << " | Cena: " << p->getPrice()
                << " | Ilosc: " << p->getQuantity()
                << " | Kategoria: " << p->getCategory()
                << " | Typ: " << p->getType()
                << "\n";
        }
        else break; 
    }
}

ProductCategory Menu::selectCategory() const {
    int choice = 0;
    std::cout << "\nWybierz kategorie:\n";
    std::cout << "0. Wszystkie\n1. Coffee\n2. Grinder\n3. Brewer\n4. CoffeeMachine\n";
    std::cout << "Wybor: ";
    std::cin >> choice;

    switch (choice) {
    case 1: return ProductCategory::Coffee;
    case 2: return ProductCategory::Grinder;
    case 3: return ProductCategory::Brewer;
    case 4: return ProductCategory::CoffeeMachine;
    default: return ProductCategory::All;
    }
}

SortField Menu::selectSortField() const {
    int choice = 0;
    std::cout << "\nSortuj wedlug:\n1. ID\n2. Cena\nWybor: ";
    std::cin >> choice;
    return (choice == 2) ? SortField::Price : SortField::Id;
}

SortOrder Menu::selectSortOrder() const {
    int choice = 0;
    std::cout << "\nKolejnosc sortowania:\n1. Rosnaco\n2. Malejaco\nWybor: ";
    std::cin >> choice;
    return (choice == 2) ? SortOrder::Desc : SortOrder::Asc;
}