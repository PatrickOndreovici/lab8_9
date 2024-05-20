//
// Created by Patrick Ondreovici on 18.04.2024.
//

#ifndef LAB6_MEDICAMENTUI_H
#define LAB6_MEDICAMENTUI_H
#include "MedicamentService.h"

class MedicamentUI {
private:
    MedicamentService& medicamentService;
public:
    MedicamentUI(MedicamentService& medicamentService) : medicamentService{medicamentService}{
    }
    void startUI();
    void printMedicament(const Medicament& medicament);
};


#endif //LAB6_MEDICAMENTUI_H
