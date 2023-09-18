#ifndef DOG_SHELTER_TESTSERVICE_H
#define DOG_SHELTER_TESTSERVICE_H
#include "../bussiness/Service.h"

class TestService {
private:
    static void testAdd();
    static void testRemove();
    static void testUpdate();
    static void testUndoAdminCommand();
    static void testRedoAdminCommand();
    static void testNextDog();
    static void testAddToAdoptionList();
    static void testRemoveFromAdoptionList();
    static void testUndoUserCommand();
    static void testRedoUserCommand();
    static void testFilter();
    static void testIsNegativeInteger();
public:
    TestService();
};
#endif //DOG_SHELTER_TESTSERVICE_H
