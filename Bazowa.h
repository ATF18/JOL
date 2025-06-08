#pragma once

#include <SFML/Graphics.hpp>

/*
  Bazowa klasa dla wszystkich obiektów w grze.
  Definiuje wspólny interfejs: aktualizację, rysowanie
  oraz pobranie obrysu do kolizji.
*/
class Bazowa {
public:
    virtual ~Bazowa() = default;

    // Wywoływane co klatkę (delta czasu w sekundach)
    virtual void aktualizuj(float dt) = 0;

    // Rysuje obiekt na przekazanym celu
    virtual void rysuj(sf::RenderTarget& cel) const = 0;

    // Zwraca obrys obiektu do detekcji kolizji
    virtual sf::FloatRect pobierzObrys() const = 0;
};
