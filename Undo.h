//
// Created by Patrick Ondreovici on 16.05.2024.
//

#ifndef LAB6_UNDO_H
#define LAB6_UNDO_H

#include "Medicament.h"
#include "MedicamentRepo.h"

class Undo {
public:
    virtual void doUndo() = 0;

    virtual ~Undo() {};
};

class UndoAdauga : public Undo {
    Medicament medicamentAdaugat;
    RepoAbstract &Repo;
public:
    UndoAdauga(RepoAbstract &repo, const Medicament &o) : Repo{repo}, medicamentAdaugat{o} {}

    void doUndo() override {
        Repo.deleteMed(medicamentAdaugat);
    }
};


class UndoModifica : public Undo {
    Medicament medicamentVechi, medicamentNou;
    RepoAbstract &Repo;
public:
    UndoModifica(RepoAbstract &repo, Medicament &ofertaVeche, Medicament &ofertaNoua) : Repo{repo}, medicamentVechi{ofertaVeche},
                                                                                medicamentNou{ofertaNoua} {}

    void doUndo() override {
        Repo.deleteMed(medicamentNou);
        Repo.store(medicamentNou);
    }
};

class UndoSterge : public Undo {
    Medicament medicamentSters;
    RepoAbstract &Repo;
public:
    UndoSterge(RepoAbstract &repo, Medicament &ofertaStearsa) : Repo{repo}, medicamentSters{ofertaStearsa} {}

    void doUndo() override {
        Repo.store(medicamentSters);
    }
};


#endif //LAB6_UNDO_H
