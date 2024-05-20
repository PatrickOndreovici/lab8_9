//
// Created by Patrick Ondreovici on 11.04.2024.
//

#ifndef LAB6_MEDICAMENT_H
#define LAB6_MEDICAMENT_H
#include <string>
#include <iostream>
using std::string;
using std::cout;

class Medicament{
private:
    string denumire;
    string producator;
    string substantaActiva;
    double pret;

    bool _equals(const Medicament& other) const;

public:
    string getDenumire() const;
    string getProducator() const;
    string getSubstantaActiva() const;
    double getPret() const;
    void setDenumire(string denumire);
    void setProducator(string producator);
    void setSubstantaActiva(string substantaActiva);
    void setPret(double pret);
    Medicament(string denumire, string producator, string substantaActiva, double pret);

    Medicament(const Medicament& medicament) : denumire {medicament.denumire}, producator {medicament.producator},
                                                substantaActiva {medicament.substantaActiva}, pret {medicament.pret}{
        cout << "*\n";
    }
    Medicament() = default;

    Medicament(string denumire);

    bool operator==(Medicament const & other) const {
        return this->_equals(other);
    }

};


#endif //LAB6_MEDICAMENT_H
