//
// Created by Patrick Ondreovici on 10.05.2024.
//

#ifndef LAB6_RETETA_H
#define LAB6_RETETA_H
#include <vector>
#include "Medicament.h"
using std::vector;
class Reteta {
private:
    vector <Medicament> medicamente;
public:
    void store(const Medicament& medicament){
        medicamente.push_back(medicament);
    }

    vector <Medicament> getAll(){
        return medicamente;
    }

    void clear(){
        medicamente.clear();
    }
};


#endif //LAB6_RETETA_H
