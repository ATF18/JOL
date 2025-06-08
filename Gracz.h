#pragma once

#include "Bazowa.h"
#include <SFML/Graphics.hpp>

/*
  Bohater: czarny prostokąt,
  porusza się A/D, skacze Space.
*/
class Gracz : public Bazowa {
public:
    // prędkość skoku (używana wewnątrz obsluzSterowanie)
    static constexpr float SKOK        = 500.f;
    static constexpr float PREDKOSC_CHODZENIA = 200.f;
    static constexpr float GRAWITACJA         = 1200.f;

    Gracz();

    // A/D = ruch poziomy, Space = skok (tylko gdy stoi na ziemi)
    void obsluzSterowanie();

    // Grawitacja + ruch wg wektora predkosc_
    void aktualizuj(float dt) override;

    // Rysowanie prostokąta
    void rysuj(sf::RenderTarget& cel) const override;

    // Do kolizji: obrys prostokąta
    sf::FloatRect pobierzObrys() const override;
    void ustawPozycje(const sf::Vector2f& poz);

    // Stan „na ziemi” i prędkość
    bool                isOnGround()  const { return naZiemi_; }
    void                setOnGround(bool v) { naZiemi_ = v; }
    const sf::Vector2f& getVelocity() const { return predkosc_; }
    void                setVelocity(const sf::Vector2f& v) { predkosc_ = v; }

private:
    sf::RectangleShape  ksztalt_;
    sf::Vector2f        predkosc_;
    bool                naZiemi_;
};
