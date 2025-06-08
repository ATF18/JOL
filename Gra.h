// include/Gra.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Zasoby.h"
#include "Bazowa.h"
#include "Gracz.h"
#include "Ziemia.h"
#include "Platforma.h"

enum class StanGry { W_TOKU, Koniec };

class Gra {
public:
    Gra();
    void uruchom();     // główna pętla

private:
    void obsluzZdarzenia();
    void aktualizuj(float dt);
    void rysuj();
    void wczytajNajwyzszyWynik();
    void zapiszNajwyzszyWynik();

    sf::RenderWindow okno_;
    ZarzadcaZasobow<sf::Texture> menTekstur_;
    ZarzadcaZasobow<sf::Font> menCzcionek_;

    std::unique_ptr<Gracz> gracz_;
    std::vector<std::unique_ptr<Bazowa>> encje_;  // tu zmienione: Encja → Bazowa

    StanGry stan_ = StanGry::W_TOKU;
    int wynik_ = 0;
    int najwyzszyWynik_ = 0;
    sf::Text tekstWyniku_;
    sf::Text tekstKoniec_;
};
