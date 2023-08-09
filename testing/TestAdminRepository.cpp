#include "TestAdminRepository.h"

TestAdminRepository::TestAdminRepository() {
    testAdd();
    testRemove();
    testUpdate();
}

void TestAdminRepository::testAdd() {
    AdminRepository<Dog> adminRepository("sample.txt");

    Dog d1("Cooper", "Akita", "Photo link", 4);
    adminRepository.add(d1);
    assert(adminRepository.getItems().size() == 1);
    assert(adminRepository.getItems()[0] == d1);
    assert(adminRepository.getIndex(d1) == 0);

    Dog d2("Cooper", "Akita", "Photo link", 4);

    try {
        adminRepository.add(d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    d2.setName("Daisy");
    adminRepository.add(d2);
    assert(adminRepository.getItems().size() == 2);
    assert(adminRepository.getItems()[1] == d2);
    assert(adminRepository.getIndex(d2) == 1);

    adminRepository.clearFile();
}

void TestAdminRepository::testRemove() {
    AdminRepository<Dog> adminRepository("sample.txt");

    Dog d1("Cooper", "Akita", "Photo link", 4);
    Dog d2("Daisy", "Akita", "Photo link", 4);

    adminRepository.add(d1);
    adminRepository.add(d2);
    assert(adminRepository.getItems().size() == 2);

    adminRepository.remove(d1);

    try {
        adminRepository.remove(d1);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Item not found!");
    }

    assert(adminRepository[0] == d2);
    adminRepository.remove(d2);

    try {
        adminRepository.remove(d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Item not found!");
    }

    adminRepository.clearFile();
}

void TestAdminRepository::testUpdate() {
    AdminRepository<Dog> adminRepository("sample.txt");
    adminRepository.clearFile();

    Dog d1("Cooper", "Akita", "Photo link", 4);
    Dog d2("Cooper", "Akita", "Photo link", 5);

    try {
        adminRepository.update(d1, d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Item not found!");
    }

    adminRepository.add(d1);

    try {
        adminRepository.update(d1, d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The new item already exists in the repository!");
    }

    d2.setName("Daisy");
    adminRepository.update(d1, d2);
    assert(adminRepository[0].getName() == "Daisy");
    assert(adminRepository.getItems().size() == 1);

    adminRepository.clearFile();
}