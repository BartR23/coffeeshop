#include <iostream>
#include <memory>
#include "PostgresProductRepository.h"
#include "Menu.h"
#include <conio.h>

std::string getPassword() {
    std::string pwd; char ch;
    std::cout << "Podaj haslo do bazy: ";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && !pwd.empty()) { pwd.pop_back(); std::cout << "\b \b"; }
        else if (ch != '\b') { pwd += ch; std::cout << '*'; }
    }
    std::cout << std::endl;
    return pwd;
}

int main() {

    std::string password = getPassword();

    std::string connStr = "dbname=coffeeshop user=postgres password=" + password + " host=localhost port=5432";
    PostgresProductRepository repo(connStr);

    Menu menu(repo);

    menu.run();

    std::cout << "Program zakończony.\n";

    return 0;
}



