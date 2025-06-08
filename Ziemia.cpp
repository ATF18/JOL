#include "Ziemia.h"
static constexpr float SCROLL_SPEED = 150.f;

Ziemia::Ziemia(const sf::Vector2f& poz) {
    ksztalt_.setSize({50.f,50.f});
    ksztalt_.setFillColor(sf::Color(180,230,255));
    ksztalt_.setPosition(poz);
}

void Ziemia::aktualizuj(float dt) {
    ksztalt_.move(-SCROLL_SPEED * dt, 0);
}

void Ziemia::rysuj(sf::RenderTarget& cel) const {
    cel.draw(ksztalt_);
}

sf::FloatRect Ziemia::pobierzObrys() const {
    return ksztalt_.getGlobalBounds();
}
