#ifndef KEEP_CALM_AND_ADOPT_A_PET_TESTADMINREPOSITORY_H
#define KEEP_CALM_AND_ADOPT_A_PET_TESTADMINREPOSITORY_H
#include "../domain/Dog.h"
#include "../infrastructure/AdminRepository.h"

class TestAdminRepository {
private:
    static void testAdd();
    static void testRemove();
    static void testUpdate();
public:
    TestAdminRepository();
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_TESTADMINREPOSITORY_H
