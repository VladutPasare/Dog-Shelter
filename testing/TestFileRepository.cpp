#include "TestFileRepository.h"

TestFileRepository::TestFileRepository() {
    testAdd();
    testRemove();
    testUpdate();
}

void TestFileRepository::testAdd() {
    FileRepository<Dog> fileRepository("../files/sample.txt");

    Dog d1("Cooper", "Akita", "Photo linkField", 4);
    fileRepository.add(d1);
    assert(fileRepository.getItems().size() == 1);
    assert(fileRepository.getItems()[0] == d1);
    assert(fileRepository.getIndex(d1) == 0);

    Dog d2("Cooper", "Akita", "Photo linkField", 4);

    try {
        fileRepository.add(d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    d2.setName("Daisy");
    fileRepository.add(d2);
    assert(fileRepository.getItems().size() == 2);
    assert(fileRepository.getItems()[1] == d2);
    assert(fileRepository.getIndex(d2) == 1);

    fileRepository.clearFile();
}

void TestFileRepository::testRemove() {
    FileRepository<Dog> fileRepository("../files/sample.txt");

    Dog d1("Cooper", "Akita", "Photo linkField", 4);
    Dog d2("Daisy", "Akita", "Photo linkField", 4);

    fileRepository.add(d1);
    fileRepository.add(d2);
    assert(fileRepository.getItems().size() == 2);

    fileRepository.remove(d1);

    try {
        fileRepository.remove(d1);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    assert(fileRepository[0] == d2);
    fileRepository.remove(d2);

    try {
        fileRepository.remove(d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    fileRepository.clearFile();
}

void TestFileRepository::testUpdate() {
    FileRepository<Dog> fileRepository("../files/sample.txt");
    fileRepository.clearFile();

    Dog d1("Cooper", "Akita", "Photo linkField", 4);
    Dog d2("Charlie", "Akita", "Photo linkField", 5);
    Dog d3("Charlie", "Akita", "Photo Link", 7);
    try {
        fileRepository.update(d1, d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    fileRepository.add(d1);
    fileRepository.add(d2);
    try {
        fileRepository.update(d1, d3);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The new item already exists in the repository!");
    }

    d3.setName("Daisy");
    fileRepository.update(d1, d3);
    assert(fileRepository[1].getName() == "Daisy");
    assert(fileRepository.getItems().size() == 2);

    fileRepository.clearFile();
}