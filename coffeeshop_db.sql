
CREATE TABLE products (
    -- Podstawa (Product)
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    price NUMERIC(10,2) NOT NULL,
    quantity INT NOT NULL,

    -- Identyfikacja typu
    category TEXT NOT NULL, -- Coffee, Grinder, Brewer, CoffeeMachine

    -- ===== Coffee =====
    coffee_form TEXT,       -- Bean / Ground
    roast_level TEXT,       -- Light / Medium / Dark
    origin_country TEXT,
    weight_grams INT,

    -- ===== Grinder =====
    grinder_type TEXT,      -- Hand / Automatic
    burr_type TEXT,         -- Conical / Flat
    for_espresso BOOLEAN,

    -- ===== Brewer =====
    brewer_type TEXT,       -- Dripper / FrenchPress / CoffeePot
    material TEXT,
    servings INT,

    -- ===== CoffeeMachine =====
    machine_type TEXT,      -- PourOver / Piston / Automatic
    power_watts INT,
    milk_frother BOOLEAN,
    capacity_ml INT
);

SELECT * FROM products;
