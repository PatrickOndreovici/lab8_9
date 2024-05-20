//
// Created by Patrick Ondreovici on 19.04.2024.
//

#ifndef LAB6_MEDICAMENTSERVICETEST_H
#define LAB6_MEDICAMENTSERVICETEST_H

class MedicamentServiceTest {
private:
    void testAddMedicament();
    void testUpdateMedicament();
    void testDeleteMedicament();
    void testFilterByPriceAndSubstance();
    void testSortMedicamente();
    void testAddToReteta();
    void testClearReteta();
    void testGenerateRandomReteta();
    void testExportReteta();
public:
    void testAll();
};


#endif //LAB6_MEDICAMENTSERVICETEST_H
