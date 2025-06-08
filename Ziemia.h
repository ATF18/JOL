#pragma once
#include "Bazowa.h"
#include <SFML/Graphics.hpp>

class Ziemia : public Bazowa {
public:
    Ziemia(const sf::Vector2f& pozycja);

    void aktualizuj(float dt) override;
    void rysuj(sf::RenderTarget& cel) const override;
    sf::FloatRect pobierzObrys() const;

private:
    sf::RectangleShape ksztalt_;  // kwadrat ziemi
    static constexpr float ROZMIAR = 50.f;
};
