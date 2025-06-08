#include "Gra.h"
#include "Gracz.h"
#include "Ziemia.h"
#include "Platforma.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>

static constexpr int   WINDOW_W     = 800;
static constexpr int   WINDOW_H     = 600;
static constexpr float TILE_SIZE    = 50.f;
static constexpr float GROUND_Y     = WINDOW_H - TILE_SIZE;
static constexpr float SCROLL_SPEED = 150.f;

// Generatory do dziur i platform
static std::mt19937 rng{std::random_device{}()};
static std::uniform_real_distribution<float> holeDist(0.f,1.f);
static std::uniform_real_distribution<float> platDist(0.f,1.f);

// Pomocnicza: generuje ziemię lub dziurę, ewentualnie platformę
static void generujSegment(std::vector<std::unique_ptr<Bazowa>>& encje, float x) {
    if (holeDist(rng) < 0.15f) return;  // dziura
    encje.push_back(std::make_unique<Ziemia>(sf::Vector2f(x, GROUND_Y)));
    if (platDist(rng) < 0.1f) {
        float y = GROUND_Y - 100.f - platDist(rng)*100.f;
        encje.push_back(std::make_unique<Platforma>(
            sf::Vector2f(x, y),
            sf::Vector2f(TILE_SIZE, 20.f)
        ));
    }
}

Gra::Gra()
: okno_({WINDOW_W, WINDOW_H}, "Ice-Man Clone")
, stan_(StanGry::W_TOKU)
{
    okno_.setFramerateLimit(60);

    // 1) Bohater
    {
        auto gr = std::make_unique<Gracz>();
        gr->ustawPozycje({WINDOW_W/4.f, GROUND_Y - 25.f});
        encje_.push_back(std::move(gr));
    }

    // 2) Pierwotne segmenty ziemi
    int ile = WINDOW_W / TILE_SIZE + 2;
    for (int i = 0; i < ile; ++i)
        generujSegment(encje_, i * TILE_SIZE);
}

void Gra::uruchom() {
    sf::Clock zegar;
    while (okno_.isOpen()) {
        obsluzZdarzenia();
        float dt = zegar.restart().asSeconds();
        if (stan_ == StanGry::W_TOKU)
            aktualizuj(dt);
        rysuj();
    }
}

void Gra::obsluzZdarzenia() {
    sf::Event ev;
    while (okno_.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            okno_.close();
        if (stan_ == StanGry::Koniec
         && ev.type == sf::Event::KeyPressed
         && ev.key.code == sf::Keyboard::R)
        {
            stan_ = StanGry::W_TOKU;
            auto* gr = static_cast<Gracz*>(encje_[0].get());
            gr->ustawPozycje({WINDOW_W/4.f, GROUND_Y - 25.f});
        }
    }
}

void Gra::aktualizuj(float dt) {
    auto* gr = static_cast<Gracz*>(encje_[0].get());

    // 1) Sterowanie i ruch gracza
    gr->obsluzSterowanie();
    gr->aktualizuj(dt);

    // 2) Kolizje: jeśli stopka (1px pod graczem) trafia w kafelek, zatrzymaj go
    bool onGround = false;
    sf::FloatRect pb = gr->pobierzObrys();
    // stopka tuż pod dolną krawędzią
    sf::FloatRect stopka(pb.left, pb.top + pb.height, pb.width, 1.f);
    for (size_t i = 1; i < encje_.size(); ++i) {
        sf::FloatRect eb = encje_[i]->pobierzObrys();
        if (stopka.intersects(eb)) {
            // ustaw gracza tuż nad eb.top
            float h = pb.height;
            float cx = pb.left + pb.width/2.f;
            float cy = eb.top - h/2.f;
            gr->ustawPozycje({cx, cy});
            gr->setVelocity({gr->getVelocity().x, 0.f});
            gr->setOnGround(true);
            onGround = true;
            break;
        }
    }
    if (!onGround)
        gr->setOnGround(false);

    // 3) Side-scroll: przesuwamy kafelki w lewo
    for (size_t i = 1; i < encje_.size(); ++i)
        encje_[i]->aktualizuj(dt);

    // 4) Usuwamy kafelki poza ekranem i generujemy nowe z prawej
    float maxX = 0.f;
    auto it = encje_.begin() + 1;
    while (it != encje_.end()) {
        auto ob = (*it)->pobierzObrys();
        if (ob.left + ob.width < 0.f) {
            it = encje_.erase(it);
        } else {
            if (dynamic_cast<Ziemia*>((*it).get()))
                maxX = std::max(maxX, ob.left);
            ++it;
        }
    }
    while (maxX < WINDOW_W + TILE_SIZE) {
        generujSegment(encje_, maxX + TILE_SIZE);
        maxX += TILE_SIZE;
    }
}

void Gra::rysuj() {
    okno_.clear(sf::Color(100, 149, 237));  // niebo

    // 1) Ziemia i platformy
    for (size_t i = 1; i < encje_.size(); ++i)
        encje_[i]->rysuj(okno_);

    // 2) Bohater
    encje_[0]->rysuj(okno_);

    okno_.display();
}
