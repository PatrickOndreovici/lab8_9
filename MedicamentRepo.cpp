//
// Created by Patrick Ondreovici on 18.04.2024.
//

#include "MedicamentRepo.h"
#include <algorithm>
#include "MedicamentException.h"
#include <fstream>
using std::find_if;
using std::swap;

/**
 *
 * @return medicamente
 */
vector<Medicament> MedicamentRepo::getAll(){
    return medicamente;
}
/**
 *
 * store medicamente
 */
void MedicamentRepo::store(const Medicament& medicament){
    medicamente.push_back(medicament);
}

/**
 * Deletes a medication from the repository.
 *
 * @param medicament The medication object to be deleted.
 */
void MedicamentRepo::deleteMed(const Medicament& medicament){
    auto it = find_if(medicamente.begin(), medicamente.end(), [&] (const Medicament &med ){
        return med == medicament;
    });
    swap(*it, medicamente[medicamente.size() - 1]);
    medicamente.pop_back();
}

/**
 * Updates an existing medication in the repository.
 *
 * @param medicament The updated medication object.
 */
void MedicamentRepo::update(const Medicament& medicament){
    auto it = find_if(medicamente.begin(), medicamente.end(), [&] (const Medicament &med ){
        return med == medicament;
    });
    if (it != medicamente.end()){
        *it = medicament;
    }

}

/**
 * Searches for a medication in the repository.
 *
 * @param medicament The medication object to search for.
 * @return True if the medication is found, otherwise false.
 */
bool MedicamentRepo::findMed(const Medicament& medicament){
    auto it = find_if(medicamente.begin(), medicamente.end(), [&] (const Medicament &med ){
                return med == medicament;
    });
    return it != medicamente.end();
}

Medicament MedicamentRepo::findByDenumire(const Medicament& medicament){
    auto it = find_if(medicamente.begin(), medicamente.end(), [&] (const Medicament &med ){
        return med == medicament;
    });
    return *it;
}


/**
 * read data from fileName file
 */
void MedicamentRepoFile::loadFromFile() {
    std::ifstream in(fileName);
    if (!in.is_open()) throw MedicamentException("Eroare la deschiderea fisierului!!!");
    while (!in.eof()) {
        string denumire;
        string producator;
        string substantaActiva;
        double pret;
        if (in.eof()) break;
        in >> denumire;
        if (in.eof()) break;
        in >> producator;
        if (in.eof()) break;
        in >> substantaActiva;
        if (in.eof()) break;
        in >> pret;
        Medicament medicament{denumire, producator, substantaActiva, pret};
        MedicamentRepo::store(medicament);
    }
    in.close();
}



/**
 * write data from fileName file
 */
void MedicamentRepoFile::writeToFile() {
    std::ofstream out(fileName);
    if (!out.is_open()) throw MedicamentException("Eroare la deschiderea fisierului!!!");
    for (auto &med: MedicamentRepo::getAll()) {
        out << med.getDenumire();
        out << std::endl;
        out << med.getProducator();
        out << std::endl;
        out << med.getSubstantaActiva();
        out << std::endl;
        out << med.getPret();
        out << std::endl;
    }
    out.close();
}