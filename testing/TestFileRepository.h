#ifndef DOG_SHELTER_TESTFILEREPOSITORY_H
#define DOG_SHELTER_TESTFILEREPOSITORY_H
#include "../domain/Dog.h"
#include "../infrastructure/FileRepository.h"

class TestFileRepository {
private:
    static void testAdd();
    static void testRemove();
    static void testUpdate();

public:
    TestFileRepository();
};

#endif //DOG_SHELTER_TESTFILEREPOSITORY_H
