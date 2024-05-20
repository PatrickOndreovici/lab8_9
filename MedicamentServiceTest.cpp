//
// Created by Patrick Ondreovici on 19.04.2024.
//

#include "MedicamentServiceTest.h"
#include "cassert"
#include "MedicamentService.h"
#include "MedicamentRepo.h"
#include "MedicamentException.h"
#include <fstream>

void MedicamentServiceTest::testAddMedicament() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Test adding a new medicament
    medicamentService.add("Aspirin", "Bayer", "Acetylsalicylic acid", 10.5);

    // Test adding an existing medicament (should throw exception)
    try {
        medicamentService.add("Aspirin", "Bayer", "Acetylsalicylic acid", 10.5);
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
    try {
        medicamentService.add("", "Bayer", "Acetylsalicylic acid", 10.5);
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
    try {
        medicamentService.add("fdafa", "Bayer", "Acetylsalicylic acid", -333);
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
}

void MedicamentServiceTest::testUpdateMedicament() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add a medicament first
    medicamentService.add("Paracetamol", "Generic", "Paracetamol", 5.0);

    // Test updating an existing medicament
    medicamentService.update("Paracetamol", "Generic", "Paracetamol", 6.0);

    // Test updating a non-existing medicament (should throw exception)
    try {
        medicamentService.update("Ibuprofen", "Generic", "Ibuprofen", 7.0);
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
    try {
        medicamentService.update("", "Generic", "Ibuprofen", 7.0);
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
    try {
        medicamentService.update("Ibuprofen", "Generic", "Ibuprofen", -7.0);
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
}

void MedicamentServiceTest::testDeleteMedicament() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add a medicament first
    medicamentService.add("Naproxen", "Generic", "Naproxen", 8.0);

    // Test deleting an existing medicament
    medicamentService.deleteMed("Naproxen");

    // Test deleting a non-existing medicament (should throw exception)
    try {
        medicamentService.deleteMed("Naproxen");
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
    try {
        medicamentService.deleteMed("");
        assert(false); // Fail the test if the exception is not thrown
    } catch (const MedicamentException& e) {
        assert(true); // Pass the test if the exception is thrown
    }
}

void MedicamentServiceTest::testFilterByPriceAndSubstance() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add some medicaments first
    medicamentService.add("Med1", "Prod1", "Subst1", 5.0);
    medicamentService.add("Med2", "Prod2", "Subst2", 10.0);
    medicamentService.add("Med3", "Prod3", "Subst3", 15.0);

    // Test filtering medicaments by price and substance
    vector<Medicament> filteredMedicaments = medicamentService.filterByPriceAndSubstance(12.0, "Subst2");
    assert(filteredMedicaments.size() == 1);
    assert(filteredMedicaments[0].getDenumire() == "Med2");

    try{
        medicamentService.filterByPriceAndSubstance(-55.0, "Subst2");
        assert(false);
    } catch (MedicamentException& ex){
        assert(true);
    }

    try{
        medicamentService.filterByPriceAndSubstance(55.0, "");
        assert(false);
    } catch (MedicamentException& ex){
        assert(true);
    }
}

void MedicamentServiceTest::testSortMedicamente() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add some medicaments first
    medicamentService.add("Med3", "Prod3", "Subst3", 15.0);
    medicamentService.add("Med1", "Prod1", "Subst1", 5.0);
    medicamentService.add("Med2", "Prod2", "Subst2", 10.0);

    // Test sorting medicaments by price
    vector<Medicament> sortedMedicamentsByPrice = medicamentService.sortMedicamente([](const Medicament& a, const Medicament& b) {
        return a.getPret() < b.getPret();
    });
    assert(sortedMedicamentsByPrice[0].getDenumire() == "Med1");
    assert(sortedMedicamentsByPrice[1].getDenumire() == "Med2");
    assert(sortedMedicamentsByPrice[2].getDenumire() == "Med3");
}

void MedicamentServiceTest::testAddToReteta() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add some medicaments first
    medicamentService.add("Med1", "Prod1", "Subst1", 5.0);
    medicamentService.add("Med2", "Prod2", "Subst2", 10.0);

    // Add medicament to reteta
    medicamentService.addToReteta("Med1");
    vector<Medicament> reteta = medicamentService.getReteta();
    assert(reteta.size() == 1);
    assert(reteta[0].getDenumire() == "Med1");

    // Attempt to add a non-existent medicament to reteta
    try {
        medicamentService.addToReteta("NonExistentMed");
        assert(false); // This should not be reached
    } catch (MedicamentException& ex) {
        assert(ex.getMessage() == "Nu exista medicamentul, nu l-am putut adauga in reteta");
    }
}

void MedicamentServiceTest::testClearReteta() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add some medicaments and add them to reteta
    medicamentService.add("Med1", "Prod1", "Subst1", 5.0);
    medicamentService.addToReteta("Med1");

    // Clear reteta
    medicamentService.clearReteta();
    vector<Medicament> reteta = medicamentService.getReteta();
    assert(reteta.empty());
}

void MedicamentServiceTest::testGenerateRandomReteta() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add some medicaments
    medicamentService.add("Med1", "Prod1", "Subst1", 5.0);
    medicamentService.add("Med2", "Prod2", "Subst2", 10.0);
    medicamentService.add("Med3", "Prod3", "Subst3", 15.0);

    // Generate random reteta with valid number of medicaments
    medicamentService.generateRandomReteta(2);
    vector<Medicament> reteta = medicamentService.getReteta();
    assert(reteta.size() == 2);

    // Attempt to generate reteta with invalid number of medicaments
    try {
        medicamentService.generateRandomReteta(0);
        assert(false); // This should not be reached
    } catch (MedicamentException& ex) {
        assert(string(ex.getMessage()) == "Numarul de medicamente trebuie sa fie mai mare de 0");
    }

    // Clear all medicaments and attempt to generate reteta
    medicamentService.deleteMed("Med1");
    medicamentService.deleteMed("Med2");
    medicamentService.deleteMed("Med3");
    try {
        medicamentService.generateRandomReteta(1);
        assert(false); // This should not be reached
    } catch (MedicamentException& ex) {
        assert(string(ex.getMessage()) == "Nu avem medicamente momentan !");
    }
}

void MedicamentServiceTest::testExportReteta() {
    MedicamentRepo medicamentRepo;
    MedicamentService medicamentService{medicamentRepo};

    // Add some medicaments and add them to reteta
    medicamentService.add("Med1", "Prod1", "Subst1", 5.0);
    medicamentService.addToReteta("Med1");
    medicamentService.addToReteta("Med1");
    medicamentService.add("Med2", "Prod2", "Subst2", 10.0);
    medicamentService.addToReteta("Med2");

    // Export reteta to CSV
    medicamentService.exportReteta("csv", "testReteta");
    std::ifstream csvFile("/Users/patrickondreovici/Desktop/lab6/testReteta.csv");
    assert(csvFile.is_open());
    std::string line;
    std::getline(csvFile, line); // Skip header
    std::getline(csvFile, line);
    assert(line == "Med1,Prod1,Subst1,5,2");
    std::getline(csvFile, line);
    assert(line == "Med2,Prod2,Subst2,10,1");
    csvFile.close();

    // Export reteta to HTML
    medicamentService.exportReteta("html", "testReteta");
    std::ifstream htmlFile("/Users/patrickondreovici/Desktop/lab6/testReteta.html");
    assert(htmlFile.is_open());
    std::string content((std::istreambuf_iterator<char>(htmlFile)), (std::istreambuf_iterator<char>()));
    assert(content.find("<td>Med1</td>") != std::string::npos);
    assert(content.find("<td>2</td>") != std::string::npos);
    assert(content.find("<td>Med2</td>") != std::string::npos);
    assert(content.find("<td>1</td>") != std::string::npos);
    htmlFile.close();

    // Attempt to export reteta in unsupported format
    try {
        medicamentService.exportReteta("txt", "testReteta");
        assert(false); // This should not be reached
    } catch (MedicamentException& ex) {
        assert(string(ex.getMessage()) == "Nu suportam formatul !");
    }
}


void MedicamentServiceTest::testAll() {
    cout << "Running tests...\n";
    testAddMedicament();
    testDeleteMedicament();
    testFilterByPriceAndSubstance();
    testSortMedicamente();
    testUpdateMedicament();
    testAddToReteta();
    testClearReteta();
    testGenerateRandomReteta();
    testExportReteta();
    cout << "Tests passed!\n";
}