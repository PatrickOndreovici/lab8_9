#include "MedicamentUI.h"
#include "MedicamentRepo.h"
#include "MedicamentServiceTest.h"
#include <fstream>
using namespace std;

int main() {
//    MedicamentServiceTest serviceTest;
//    serviceTest.testAll();
    try{
        MedicamentRepoFile medicamentRepo{"/Users/patrickondreovici/Desktop/lab6/fisier_intern.txt"};
        ProbRepo probRepo;
        probRepo.setProb(0);
        MedicamentService medicamentService{medicamentRepo};
        MedicamentUI medicamentUI{medicamentService};
        medicamentUI.startUI();
    } catch (MedicamentException& exc){
        cout << exc.getMessage() << "\n";
    }
    return 0;
}
