//
// Created by Patrick Ondreovici on 18.04.2024.
//

#ifndef LAB6_MEDICAMENTREPO_H
#define LAB6_MEDICAMENTREPO_H
#include <utility>
#include <vector>
#include "Medicament.h"
#include <random>
#include "MedicamentException.h"
using std::vector;



// clasa de repo pur abstracta
class RepoAbstract {
public:
    RepoAbstract() = default;

    virtual void store(const Medicament& medicament) = 0;

    virtual vector <Medicament> getAll() = 0;

    virtual void deleteMed(const Medicament& medicament) = 0;

    virtual bool findMed(const Medicament& medicament) = 0;

    virtual void update(const Medicament& medicament) = 0;

    virtual Medicament findByDenumire(const Medicament& medicament) = 0;

};

class MedicamentRepo : public RepoAbstract{
private:
    vector <Medicament> medicamente;
public:
    MedicamentRepo() = default;
    MedicamentRepo(const MedicamentRepo &o) = delete;
    void store(const Medicament& medicament) override;

    vector <Medicament> getAll() override;

    void deleteMed(const Medicament& medicament) override;

    bool findMed(const Medicament& medicament) override;

    void update(const Medicament& medicament) override;

    Medicament findByDenumire(const Medicament& medicament) override;
};

class MedicamentRepoFile : public MedicamentRepo {
private:
    string fileName;
    void loadFromFile();
    void writeToFile();
public:
    explicit MedicamentRepoFile(string fileName) : MedicamentRepo(), fileName{std::move(fileName)}{
        // first thing when created, load from file
        loadFromFile();
    }
    void store(const Medicament& medicament) override{
        MedicamentRepo::store(medicament);
        writeToFile();
    }
    void deleteMed(const Medicament& medicament) override{
        MedicamentRepo::deleteMed(medicament);
        writeToFile();
    }
    void update(const Medicament& medicament) override{
        MedicamentRepo::update(medicament);
        writeToFile();
    }
};


class ProbRepo : public MedicamentRepo {
private:
    double probabilitate;

    // functia ce returneaza probabilitatea
    void random(){
        double random = ((double) rand() / (RAND_MAX));
        if (random > probabilitate) {
            random *= 100;
            cout << "Probabilitatea: " << random << "\n";
            throw (MedicamentException("A crapaaaat"));
        }
    }


public:
    ProbRepo() {
        std::mt19937 gen(123);
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        probabilitate = dis(gen);
    };

    void setProb(double prob){
        this->probabilitate = prob;
    }

    ProbRepo(const MedicamentRepo &alt) = delete;

    void store(const Medicament& medicament) override{
        random();
        MedicamentRepo::store(medicament);
    }
    void deleteMed(const Medicament& medicament) override{
        random();
        MedicamentRepo::deleteMed(medicament);
    }
    void update(const Medicament& medicament) override{
        random();
        MedicamentRepo::update(medicament);
    }

    vector <Medicament> getAll() override{
        random();
        return MedicamentRepo::getAll();
    }


    bool findMed(const Medicament& medicament) override{
        random();
        return MedicamentRepo::findMed(medicament);
    }

    Medicament findByDenumire(const Medicament& medicament) override{
        random();
        return MedicamentRepo::findByDenumire(medicament);
    }
};


#endif //LAB6_MEDICAMENTREPO_H
