//
// Created by Patrick Ondreovici on 18.04.2024.
//

#include "MedicamentService.h"
#include "MedicamentException.h"
#include <random>
#include <map>
#include <fstream>
#include <utility>
#include <memory>
using SortFunction = std::function<bool(const Medicament&, const Medicament&)>;
using std::sort;
using std::copy_if;
using std::map;
using std::pair;
/**
 * Retrieves all medications stored in the repository.
 *
 * @return A vector containing all medications.
 */
vector<Medicament> MedicamentService::getAll() {
    return medicamentRepo.getAll();
}

vector <Medicament> MedicamentService::getReteta() {
    return reteta.getAll();
}

/**
 * Adds a new medication to the repository.
 *
 * @param denumire        The name of the medication.
 * @param producator      The producer of the medication.
 * @param substantaActiva The active substance of the medication.
 * @param pret            The price of the medication.
 * @throws MedicamentException if the medication already exists in the repository.
 */
void MedicamentService::add(const string& denumire, const string& producator, const string& substantaActiva, const double& pret){
    if (pret < 0){
        throw MedicamentException("Pretul trebuie sa fie mai mare de 0");
    }
    if (denumire.empty() || producator.empty() || substantaActiva.empty()){
        throw MedicamentException("Date invalide !");
    }
    Medicament medicament{denumire, producator, substantaActiva, pret};
    vector<Medicament> medicamente = getAll();
    if (medicamentRepo.findMed(medicament)){
        throw MedicamentException("Medication already exists");
    }
    medicamentRepo.store(medicament);
    undoActions.push_back(std::make_unique<UndoAdauga>(medicamentRepo, medicament));
}

/**
 * Updates an existing medication in the repository.
 *
 * @param denumire        The name of the medication.
 * @param producator      The producer of the medication.
 * @param substantaActiva The active substance of the medication.
 * @param pret            The price of the medication.
 * @throws MedicamentException if the medication doesn't exist in the repository.
 */
void MedicamentService::update(const string &denumire, const string& producator, const string& substantaActiva, const double& pret){
    if (pret < 0){
        throw MedicamentException("Pretul trebuie sa fie mai mare de 0");
    }
    if (denumire.empty() || producator.empty() || substantaActiva.empty()){
        throw MedicamentException("Date invalide !");
    }
    Medicament medicament{denumire, producator, substantaActiva, pret};
    vector<Medicament> medicamente = getAll();
    if (!medicamentRepo.findMed(medicament)){
        throw MedicamentException("Medication does not exist");
    }
    Medicament med = medicamentRepo.findByDenumire(denumire);
    medicamentRepo.update(medicament);
    undoActions.push_back(std::make_unique<UndoModifica>(medicamentRepo, medicament, med));
}

/**
 * Deletes a medication from the repository.
 *
 * @param denumire The name of the medication to be deleted.
 * @throws MedicamentException if the medication doesn't exist in the repository.
 */
void MedicamentService::deleteMed(const string &denumire){
    if (denumire.empty()){
        throw MedicamentException("Date invalide!");
    }
    Medicament medicament{denumire};
    if (!medicamentRepo.findMed(medicament)){
        throw MedicamentException("Medication does not exist, hence cannot be deleted");
    }
    Medicament med = medicamentRepo.findByDenumire(denumire);
    medicamentRepo.deleteMed(medicament);
    undoActions.push_back(std::make_unique<UndoSterge>(medicamentRepo, med));
}

/**
 * Filters medications by price and active substance.
 *
 * @param pret            The maximum price of medications to be filtered.
 * @param substantaActiva The active substance to filter by.
 * @return A vector containing medications that match the criteria.
 */
vector<Medicament> MedicamentService::filterByPriceAndSubstance(const double pret, const string substantaActiva){
    if (pret < 0){
        throw MedicamentException("Pretul trebuie sa fie mai mare de 0");
    }
    if (substantaActiva.empty()){
        throw MedicamentException("Date invalide !");
    }
    vector <Medicament> medicamente = getAll();
    vector <Medicament> medicamenteFiltrate;
    medicamenteFiltrate.reserve(medicamente.size());
    copy_if(medicamente.begin(), medicamente.end(), back_inserter(medicamenteFiltrate), [&] (const Medicament &med ){
        return med.getSubstantaActiva() == substantaActiva && med.getPret() < pret;
    });
    return medicamenteFiltrate;
}

/**
 * Sorts medications using a custom sorting function.
 *
 * @param sortFunction The custom sorting function.
 * @return A vector containing medications sorted according to the provided function.
 */
vector<Medicament> MedicamentService::sortMedicamente(SortFunction sortFunction) {
    vector<Medicament> medicamente = getAll();
    sort(medicamente.begin(), medicamente.end(), std::move(sortFunction));
    return medicamente;
}

/**
 * Adds a medication to the prescription list if it exists in the inventory.
 *
 * @param denumire The name of the medication to be added.
 * @throws MedicamentException if the medication is not found in the inventory.
 */
void MedicamentService::addToReteta(const string denumire){
    vector<Medicament> medicamente = getAll();
    auto it = find_if(medicamente.begin(), medicamente.end(), [&] (const Medicament &med ){
        return med.getDenumire() == denumire;
    });
    if (it == medicamente.end()){
        throw MedicamentException("Nu exista medicamentul, nu l-am putut adauga in reteta");
    }
    reteta.store(*it);
}

/**
 * Clears the prescription list.
 */
void MedicamentService::clearReteta(){
    reteta.clear();
}

/**
 * Generates a random prescription list with a specified number of medications.
 *
 * @param numarMedicamente The number of medications to include in the prescription list.
 * @throws MedicamentException if numarMedicamente is less than or equal to 0 or if there are no medications in the inventory.
 */
void MedicamentService::generateRandomReteta(int numarMedicamente){
    if (numarMedicamente <= 0){
        throw MedicamentException("Numarul de medicamente trebuie sa fie mai mare de 0");
    }
    vector <Medicament> medicamente = getAll();
    if (medicamente.empty()){
        throw MedicamentException("Nu avem medicamente momentan !");
    }
    reteta.clear();
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, (int)medicamente.size()-1);
    while (numarMedicamente--){
        int rndNr = dist(mt);
        reteta.store(medicamente[rndNr]);
    }
}

/**
 * Exports the prescription list to a file in the specified format (CSV or HTML).
 *
 * @param type The format to export the file ("csv" or "html").
 * @param fileName The name of the file to export to.
 * @throws MedicamentException if the format type is not supported.
 */
void MedicamentService::exportReteta(const string& type, const string& fileName) {
    map<string, pair<Medicament, int> > medicamentAndQuantity;
    vector<Medicament> medicamente = reteta.getAll();
    for (Medicament& medicament : medicamente){
        string denumire = medicament.getDenumire();
        if (medicamentAndQuantity.find(medicament.getDenumire()) != medicamentAndQuantity.end()){
            medicamentAndQuantity[denumire].second++;
        }
        else{
            medicamentAndQuantity[denumire] = {medicament, 1};
        }
    }
    if (type == "csv"){
        std::ofstream myfile;
        myfile.open ("/Users/patrickondreovici/Desktop/lab6/" + fileName + ".csv");
        myfile << "Denumire,Producator,Substanta Activa,Pret,Cantitate" << std::endl;
        for (auto &it : medicamentAndQuantity){
            Medicament medicament = it.second.first;
            myfile << medicament.getDenumire() << ","
                   << medicament.getProducator() << ","
                   << medicament.getSubstantaActiva() << ","
                   << medicament.getPret() << ","
                   << it.second.second << std::endl;
        }
        myfile.close();
    }
    else if (type == "html"){
        std::ofstream htmlFile;
        htmlFile.open("/Users/patrickondreovici/Desktop/lab6/" + fileName + ".html");
        htmlFile << "<!DOCTYPE html>" << std::endl;
        htmlFile << "<html>" << std::endl;
        htmlFile << "<head>" << std::endl;
        htmlFile << "<title>Medicamente</title>" << std::endl;
        htmlFile << "</head>" << std::endl;
        htmlFile << "<body>" << std::endl;
        htmlFile << "<table border='1'>" << std::endl;
        htmlFile << "<tr>"
                 << "<th>Denumire</th>"
                 << "<th>Producator</th>"
                 << "<th>Substanta Activa</th>"
                 << "<th>Pret</th>"
                 << "<th>Cantitate</th>"
                 << "</tr>" << std::endl;

        for (auto &it : medicamentAndQuantity) {
            Medicament medicament = it.second.first;
            htmlFile << "<tr>"
                     << "<td>" << medicament.getDenumire() << "</td>"
                     << "<td>" << medicament.getProducator() << "</td>"
                     << "<td>" << medicament.getSubstantaActiva() << "</td>"
                     << "<td>" << medicament.getPret() << "</td>"
                     << "<td>" << it.second.second << "</td>"
                     << "</tr>" << std::endl;
        }

        htmlFile << "</table>" << std::endl;
        htmlFile << "</body>" << std::endl;
        htmlFile << "</html>" << std::endl;
        htmlFile.close();
    }
    else{
        throw MedicamentException("Nu suportam formatul !");
    }
}

void MedicamentService::undo() {
    if (undoActions.empty())
        throw MedicamentException("Nu mai exista operatii pentru a se face UNDO!!!");
    undoActions.back()->doUndo();
    undoActions.pop_back();
}