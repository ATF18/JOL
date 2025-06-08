#include "Platforma.h"
static constexpr float SCROLL_SPEED = 150.f;

Platforma::Platforma(const sf::Vector2f& poz, const sf::Vector2f& roz) {
    ksztalt_.setSize(roz);
    ksztalt_.setFillColor(sf::Color(150,200,255));
    ksztalt_.setPosition(poz);
}

void Platforma::aktualizuj(float dt) {
    ksztalt_.move(-SCROLL_SPEED * dt, 0);
}

void Platforma::rysuj(sf::RenderTarget& cel) const {
    cel.draw(ksztalt_);
}

sf::FloatRect Platforma::pobierzObrys() const {
    return ksztalt_.getGlobalBounds();
}
