#include "Gracz.h"
#include <SFML/Window/Keyboard.hpp>

Gracz::Gracz()
: predkosc_{0.f, 0.f}
, naZiemi_{false}
{
    ksztalt_.setSize({30.f, 50.f});
    ksztalt_.setFillColor(sf::Color::Black);
    ksztalt_.setOrigin(ksztalt_.getSize() * 0.5f);
}

void Gracz::ustawPozycje(const sf::Vector2f& poz) {
    ksztalt_.setPosition(poz);
    predkosc_ = {0.f, 0.f};
    naZiemi_  = false;
}

void Gracz::obsluzSterowanie() {
    // Skok – tylko gdy stoi na ziemi
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && naZiemi_) {
        predkosc_.y = -SKOK;
        naZiemi_    = false;
    }

    // Ruch poziomy A/D
    predkosc_.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        predkosc_.x = -PREDKOSC_CHODZENIA;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        predkosc_.x =  PREDKOSC_CHODZENIA;
}

void Gracz::aktualizuj(float dt) {
    // Grawitacja
    predkosc_.y += GRAWITACJA * dt;
    // Przemieszczenie kształtu
    ksztalt_.move(predkosc_ * dt);
}

void Gracz::rysuj(sf::RenderTarget& cel) const {
    cel.draw(ksztalt_);
}

sf::FloatRect Gracz::pobierzObrys() const {
    return ksztalt_.getGlobalBounds();
}
