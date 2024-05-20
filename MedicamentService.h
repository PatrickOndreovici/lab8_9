//
// Created by Patrick Ondreovici on 18.04.2024.
//

#ifndef LAB6_MEDICAMENTSERVICE_H
#define LAB6_MEDICAMENTSERVICE_H
#include <utility>
#include "Undo.h"
#include "MedicamentRepo.h"
#include "Reteta.h"
#include <string>
#include <functional>
#include <vector>
#include <memory>
using SortFunction = std::function<bool(const Medicament&, const Medicament&)>;
using std::unique_ptr;
using std::function;
class MedicamentService {
private:
    RepoAbstract& medicamentRepo;
    Reteta reteta;
    std::vector<unique_ptr<Undo>> undoActions;
public:

    explicit MedicamentService(class RepoAbstract &medicamentRepo) : medicamentRepo{medicamentRepo}{}

    // Destructor
    ~MedicamentService() = default;

    // Copy constructor (deleted)
    MedicamentService(const MedicamentService&) = delete;

    // Copy assignment operator (deleted)
    MedicamentService& operator=(const MedicamentService&) = delete;

    // Move constructor
//    MedicamentService(MedicamentService&& other) noexcept
//            : medicamentRepo(std::move(other.medicamentRepo)),
//              reteta(std::move(other.reteta)),
//              undoActions(std::move(other.undoActions)) {}
    void add(const string& denumire, const string& producator, const string& substantaActiva, const double& pret);
    vector<Medicament> getAll();
    void deleteMed(const string& denumire);
    vector<Medicament> filterByPriceAndSubstance(double pret, string substantaActiva);
    void update(const string& denumire, const string& producator, const string& substantaActiva, const double& pret);
    vector<Medicament> sortMedicamente(SortFunction sortFunction);
    void addToReteta(string denumire);
    void clearReteta();
    void generateRandomReteta(int numarMedicamente);
    void exportReteta(const string& type, const string& fileName);
    vector <Medicament> getReteta();
    void undo();
};


#endif //LAB6_MEDICAMENTSERVICE_H
