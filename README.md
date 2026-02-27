# coffeeshop
A console application for managing a coffeeshop's product database

Coffeeshop to konsolowa aplikacja w C++, służąca do zarządzania bazą danych produktów
sklepu z kawą i akcesoriami kawowymi. Program umożliwia użytkownikowi:
• dodawanie produktów do bazy danych,
• przeglądanie wszystkich produktów,
• usuwanie i aktualizację istniejących produktów,
• sortowanie produktów według ID lub ceny,
• wyświetlanie statystyk cenowych (minimum, maksimum, średnia),
• filtrowanie operacji według kategorii produktów.
Dane są trwale przechowywane w bazie PostgreSQL, a aplikacja komunikuje się z nią przy
użyciu biblioteki libpqxx. Interakcja z użytkownikiem odbywa się przez menu tekstowe.
Program został zaprojektowany zgodnie z zasadami: programowania obiektowego,
polimorfizmu, separacji odpowiedzialności, wzorca Repository. Jego główne warstwy
obejmują:
1. Model domenowy – klasy produktów (Product, Coffee, Grinder, Brewer,
CoffeeMachine).
2. Warstwę dostępu do danych – IProductRepository, 
PostgresProductRepository.
3. Logikę aplikacji / UI – Menu, ProductFactory.
4. Punkt startowy – main.cpp.

Wszystkie klasy programu oraz zależności pomiędzy nimi:
• Product - klasa bazowa dla wszystkich produktów,
• Coffee, Grinder, Brewer, CoffeeMachine - dziedziczą po Product,
• Menu - korzysta z IProductRepository,
• PostgresProductRepository - implementuje IProductRepository,
• ProductFactory - tworzy obiekty pochodnych klas Product,
• Menu + ProductFactory - współpracują przy dodawaniu i aktualizacji
produktów.

Projekt Coffeeshop jest kompletną aplikacją CRUD z polimorfizmem, dziedziczeniem,
wzorcami projektowymi (Repository, Factory) oraz trwałym zapisem danych w bazie
PostgreSQL. Kod jest czytelnie podzielony na warstwy i łatwy do rozbudowy (np. o nowe
typy produktów lub inne źródło danych).
