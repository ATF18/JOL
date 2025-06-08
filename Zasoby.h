#pragma once
#include <map>
#include <memory>
#include <string>

// Szablonowy menedżer zasobów (tekstur, czcionek…)
template<typename Zasob>
class ZarzadcaZasobow {
public:
    // Ładuje zasób z pliku pod kluczem
    bool zaladuj(const std::string& klucz, const std::string& sciezka) {
        auto zas = std::make_shared<Zasob>();
        if (!zas->loadFromFile(sciezka))
            return false;
        zasoby_[klucz] = zas;
        return true;
    }

    // Pobiera zasób po kluczu
    std::shared_ptr<Zasob> pobierz(const std::string& klucz) const {
        auto it = zasoby_.find(klucz);
        if (it != zasoby_.end())
            return it->second;
        return nullptr;
    }

private:
    std::map<std::string, std::shared_ptr<Zasob>> zasoby_;
};
