//
// Created by Patrick Ondreovici on 18.04.2024.
//

#include "MedicamentUI.h"
#include <iostream>
#include "MedicamentException.h"

using std::cin;
using std::string;
using std::cout;

void MedicamentUI::startUI() {
    bool running = true;
    while (running){
        cout << "1 Adauga\n2 Sterge\n3 Printeaza\n4 Filtrare\n5 Update\n6 Afiseaza sortate\n7 Adauga in retata\n8 export reteta\n9 creeaza reteta random\n10 Clear reteta\n11 Export reteta\n 12 Undo\n 0 Exit\n";
        int cmd = 0;
        cin >> cmd;
        if (cmd == 1){
            string denumire;
            string producator;
            string substantaActiva;
            double pret;
            cout << "denumire: ";
            cin >> denumire;
            cout << "producator: ";
            cin >> producator;
            cout << "substanta activa: ";
            cin >> substantaActiva;
            cout << "pret: ";
            cin >> pret;
            try{
                medicamentService.add(denumire, producator, substantaActiva, pret);
                cout << "Medicament adaugat\n";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 2){
            string denumire;
            cout << "denumire: ";
            cin >> denumire;
            try{
                medicamentService.deleteMed(denumire);
                cout << "Medicament sters\n";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 3){
            vector <Medicament> medicamente = medicamentService.getAll();
            if (medicamente.size() == 0){
                cout << "Nu exista medicamente!\n";
            }
            for (Medicament& medicament : medicamente){
                printMedicament(medicament);
            }
        }
        else if (cmd == 4){
            string substantaActiva;
            double pret;
            cout << "substanta activa: ";
            cin >> substantaActiva;
            cout << "pret: ";
            cin >> pret;
            vector <Medicament> medicamente = medicamentService.filterByPriceAndSubstance(pret, substantaActiva);
            if (medicamente.size() == 0){
                cout << "Nu exista medicamente dupa filtare!\n";
            }
            for (Medicament& medicament : medicamente){
                printMedicament(medicament);
            }
        }
        else if (cmd == 5){
            string denumire;
            string producator;
            string substantaActiva;
            double pret;
            cout << "denumire: ";
            cin >> denumire;
            cout << "producator: ";
            cin >> producator;
            cout << "substanta activa: ";
            cin >> substantaActiva;
            cout << "pret: ";
            cin >> pret;
            try{
                medicamentService.update(denumire, producator, substantaActiva, pret);
                cout << "Medicament Updatat\n";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 6){
            cout << "1 dupa denumire\n";
            cout << "2 dupa producator\n";
            cout << "3 dupa pret\n";
            int cmdSort;
            cin >> cmdSort;
            vector <Medicament> medicamente;
            if (cmdSort == 1){
                medicamente = medicamentService.sortMedicamente([](const Medicament& a, const Medicament& b) {
                    return a.getDenumire() < b.getDenumire();
                });
            }
            else if (cmdSort == 2){
                medicamente = medicamentService.sortMedicamente([](const Medicament& a, const Medicament& b) {
                    return a.getProducator() < b.getProducator();
                });
            }
            else if (cmdSort == 3){
                medicamente = medicamentService.sortMedicamente([](const Medicament& a, const Medicament& b) {
                    return a.getPret() < b.getPret();
                });
            }
            else{
                cout << "Sortare invalida!\n";
                continue;
            }
            for (Medicament& medicament : medicamente){
                printMedicament(medicament);
            }
        }
        else if (cmd == 7){
            string denumire;
            cout << "denumire: ";
            cin >> denumire;
            try{
                medicamentService.addToReteta(denumire);
                cout << "Medicament adaugat in reteta\n";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 8){
            string type, fileName;
            cout << "tip: ";
            cin >> type;
            cout << "nume fisier: ";
            cin >> fileName;
            try{
                medicamentService.exportReteta(type, fileName);
                cout << "Export reusit !\n";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 9){
            int nrMedicamente;
            cout << "Nummar medicamente: ";
            cin >> nrMedicamente;
            try{
                medicamentService.generateRandomReteta(nrMedicamente);
                cout << "Reteta random creata !\n";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 10){
            string tip;
            string fileName;
            cin >> tip >> fileName;
            try{
                medicamentService.exportReteta(tip, fileName);
                cout << "Reteta cleared!";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 11){
            try{
                medicamentService.clearReteta();
                cout << "Reteta cleared!";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 12){
            try{
                medicamentService.undo();
                cout << "Undo realizat!";
            } catch (MedicamentException& exc){
                cout << exc.getMessage() << "\n";
            }
        }
        else if (cmd == 0){
            running = false;
        }
    }
}


void MedicamentUI::printMedicament(const Medicament& medicament){
    cout << "denumire: " << medicament.getDenumire() << "\n"
         << "producator: " << medicament.getProducator() << "\n";
    cout << "substanta activa: " << medicament.getSubstantaActiva() << "\n";
    cout << "pret: " << medicament.getPret() << "\n\n";
}
