#ifndef KEEP_CALM_AND_ADOPT_A_PET_TESTSERVICE_H
#define KEEP_CALM_AND_ADOPT_A_PET_TESTSERVICE_H
#include "../bussiness/Service.h"

class TestService {
private:
    static void testAdd();
    static void testRemove();
    static void testUpdate();
    static void testNextDog();
    static void testAddToAdoptionList();
    static void testRemoveFromAdoptionList();
    static void testFilter();
    static void testNextDogInFilteredList();
    static void testAddToAdoptionListFromFilteredList();
    static void testIsNegativeInteger();
public:
    TestService();
};
#endif //KEEP_CALM_AND_ADOPT_A_PET_TESTSERVICE_H
