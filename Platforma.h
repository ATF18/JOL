#pragma once
#include "Bazowa.h"
#include <SFML/Graphics.hpp>

class Platforma : public Bazowa {
public:
    Platforma(const sf::Vector2f& pozycja, const sf::Vector2f& rozmiar);

    void aktualizuj(float dt) override;
    void rysuj(sf::RenderTarget& cel) const override;
    sf::FloatRect pobierzObrys() const;

private:
    sf::RectangleShape ksztalt_;  // prostokąt platformy
};
