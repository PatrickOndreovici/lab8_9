//
// Created by Patrick Ondreovici on 11.04.2024.
//

#include "Medicament.h"

#include <utility>

string Medicament::getDenumire() const {
    return denumire;
}

string Medicament::getSubstantaActiva() const {
    return substantaActiva;
}

string Medicament::getProducator() const {
    return producator;
}

double Medicament::getPret() const {
    return pret;
}

Medicament::Medicament(string denumire, string producator, string substantaActiva, double pret) {
    this->denumire = std::move(denumire);
    this->producator = std::move(producator);
    this->substantaActiva = std::move(substantaActiva);
    this->pret = pret;
}

Medicament::Medicament(std::string denumire) {
    this->denumire = std::move(denumire);
    this->substantaActiva = "";
    this->producator = "";
    this->pret = 0.0;
}


bool Medicament::_equals(const Medicament& other) const{
    return this->denumire == other.denumire;
}

