#include "TestService.h"
#include <cassert>
#include "../exceptions/ServiceException.h"

TestService::TestService() {
    testAdd();
    testRemove();
    testUpdate();
    testNextDog();
    testUndoAdminCommand();
    testRedoAdminCommand();
    testAddToAdoptionList();
    testRemoveFromAdoptionList();
    testUndoUserCommand();
    testRedoUserCommand();
    testFilter();
    testIsNegativeInteger();
}

void TestService::testAdd() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    try {
        service.add("", "Akita", "link", 1);
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "Invalid name!");
    }
    assert(service.getDogsFromShelter().empty());
    service.add("Cooper", "Akita", "link", 4);
    assert(service.getDogsFromShelter().size() == 1);
    assert(service.getDogsFromShelter()[0].getName() == "Cooper");
    assert(service.getDogsFromShelter()[0].getBreed() == "Akita");

    try {
        service.add("Cooper", "Akita", "link", 4);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    admin_repository->clearFile();
}

void TestService::testRemove() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Cooper", "Akita", "link", 4);
    service.add("Daisy", "Akita", "link", 2);
    assert(service.getDogsFromShelter().size() == 2);

    assert(service.getDogsFromShelter()[1].getName() == "Daisy");
    service.remove(0);
    assert(service.getDogsFromShelter().size() == 1);
    service.remove(0);
    assert(service.getDogsFromShelter().empty());

    admin_repository->clearFile();
}

void TestService::testUpdate() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Cooper", "Akita", "link", 4);
    service.add("Charlie", "Akita", "link", 4);

    service.update(0, "Daisy", "Akita", "link", 4);
    assert(service.getDogsFromShelter()[1].getName() == "Daisy");
    assert(service.getDogsFromShelter().size() == 2);

    try {
        service.update(1, "Charlie", "Akita", "link", 4);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "The new item already exists in the repository!");
    }
    admin_repository->clearFile();
}

void TestService::testNextDog() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    try {
        service.reset_filtered_list();
        const Dog& dog = service.nextDog();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dogs for this filtering!");
    }

    service.add("Cooper", "Akita", "link", 4);
    service.add("Daisy", "Akita", "link", 2);

    service.reset_filtered_list();
    const Dog& dog1 = service.nextDog();
    assert(dog1.getName() == "Cooper");
    const Dog& dog2 = service.nextDog();
    assert(dog2.getName() == "Daisy");
    const Dog& dog3 = service.nextDog();
    assert(dog3 == dog1);

    admin_repository->clearFile();
}

void TestService::testUndoAdminCommand() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Daisy", "Akita", "link", 3);
    service.add("Cooper", "Akita", "link", 1);
    service.remove(0);

    service.update(0, "Cooper", "Akita", "link", 5);

    assert(service.getDogsFromShelter()[0].getAge() == 5);
    service.undoAdminCommand();
    assert(service.getDogsFromShelter()[1].getAge() == 1);

    service.undoAdminCommand();

    assert(service.getDogsFromShelter()[1].getName() == "Daisy");
    assert(service.getDogsFromShelter().size() == 2);

    service.undoAdminCommand();
    assert(service.getDogsFromShelter()[0].getName() == "Daisy");
    assert(service.getDogsFromShelter().size() == 1);

    service.undoAdminCommand();
    try {
        service.undoAdminCommand();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "Cannot undo!");
    }
    admin_repository->clearFile();
}

void TestService::testRedoAdminCommand() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Daisy", "Akita", "link", 3);
    service.remove(0);
    service.add("Cooper", "Akita", "link", 1);

    service.undoAdminCommand();
    service.redoAdminCommand();
    assert(service.getDogsFromShelter()[0].getName() == "Cooper");
    assert(service.getDogsFromShelter().size() == 1);

    try {
        service.redoAdminCommand();
        assert(false);
    }
    catch(const ServiceException& e) {
        assert(e.getErrorMessage() == "Cannot redo!");
    }

    service.undoAdminCommand();
    assert(service.getDogsFromShelter().empty());

    service.undoAdminCommand();
    service.redoAdminCommand();
    assert(service.getDogsFromShelter().empty());
    service.undoAdminCommand();

    service.update(0, "Charlie", "Akita", "link", 3);
    assert(service.getDogsFromShelter()[0].getName() == "Charlie");
    service.undoAdminCommand();
    assert(service.getDogsFromShelter()[0].getName() == "Daisy");
    service.redoAdminCommand();
    assert(service.getDogsFromShelter()[0].getName() == "Charlie");

    admin_repository->clearFile();
}

void TestService::testAddToAdoptionList() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Cooper", "Akita", "link", 4);
    service.add("Daisy", "Akita", "link", 2);

    Dog d1("Cooper", "Akita", "link", 4);
    Dog d2("Daisy", "Akita", "link", 2);
    assert(service.getAdoptedDogs().empty());

    service.reset_filtered_list();
    service.addToAdoptionList(d1);
    assert(service.getAdoptedDogs().size() == 1);

    service.addToAdoptionList(d2);
    assert(service.getAdoptedDogs()[0].getName() == "Cooper");

    try {
        service.addToAdoptionList(d1);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    service.add("Cooper", "Akita", "link", 4);
    try {
        service.addToAdoptionList(d1);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    admin_repository->clearFile();
    user_repository->clearFile();
}

void TestService::testRemoveFromAdoptionList() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);

    Service service(admin_repository, user_repository);

    service.add("Cooper", "Akita", "link", 4);
    service.add("Daisy", "Akita", "link", 2);
    service.add("Charlie", "Akita", "link", 3);
    Dog d1("Cooper", "Akita", "link", 4);
    Dog d2("Daisy", "Akita", "link", 2);
    Dog d3("Charlie", "Akita", "link", 3);

    service.reset_filtered_list();
    service.addToAdoptionList(d1);
    service.addToAdoptionList(d2);
    service.addToAdoptionList(d3);

    assert(service.getAdoptedDogs()[0].getName() == "Cooper");
    assert(service.getAdoptedDogs()[1].getName() == "Daisy");
    assert(service.getAdoptedDogs()[2].getName() == "Charlie");

    service.removeFromAdoptionList(1);
    assert(service.getAdoptedDogs().size() == 2);
    assert(service.getAdoptedDogs()[0].getName() == "Cooper");
    assert(service.getAdoptedDogs()[1].getName() == "Charlie");

    service.removeFromAdoptionList(0);
    assert(service.getAdoptedDogs().size() == 1);
    assert(service.getAdoptedDogs()[0].getName() == "Charlie");

    service.removeFromAdoptionList(0);
    assert(service.getAdoptedDogs().empty());

    // dogs added back to admin repo
    assert(service.getDogsFromShelter()[0].getName() == "Daisy");
    assert(service.getDogsFromShelter()[1].getName() == "Cooper");
    assert(service.getDogsFromShelter()[2].getName() == "Charlie");
    assert(service.getDogsFromShelter().size() == 3);

    admin_repository->clearFile();
    user_repository->clearFile();
}

void TestService::testUndoUserCommand() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Daisy", "Akita", "link", 1);
    service.add("Cooper", "Akita", "link", 1);

    service.reset_filtered_list();
    service.addToAdoptionList(Dog("Daisy", "Akita", "link", 1));
    service.addToAdoptionList(Dog("Cooper", "Akita", "link", 1));
    service.removeFromAdoptionList(1);
    service.undoUserCommand();

    assert(service.getAdoptedDogs()[0].getName() == "Daisy");
    assert(service.getAdoptedDogs()[1].getName() == "Cooper");
    assert(service.getAdoptedDogs().size() == 2);

    service.undoUserCommand();
    assert(service.getAdoptedDogs()[0].getName() == "Daisy");
    assert(service.getAdoptedDogs().size() == 1);

    service.undoUserCommand();
    assert(service.getAdoptedDogs().empty());

    try {
        service.undoUserCommand();
        assert(false);
    }
    catch(const ServiceException& e) {
        assert(e.getErrorMessage() == "Cannot undo!");
    }
    admin_repository->clearFile();
    user_repository->clearFile();
}

void TestService::testRedoUserCommand() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Daisy", "Akita", "link", 1);
    service.add("Cooper", "Akita", "link", 1);
    service.add("Charlie", "Akita", "link", 2);

    service.reset_filtered_list();
    service.addToAdoptionList(Dog("Daisy", "Akita", "link", 1));
    service.removeFromAdoptionList(0);
    service.addToAdoptionList(Dog("Cooper", "Akita", "link", 1));
    service.addToAdoptionList(Dog("Charlie", "Akita", "link", 2));

    try {
        service.redoUserCommand();
    }
    catch(const ServiceException& e) {
        assert(e.getErrorMessage() == "Cannot redo!");
    }

    service.undoUserCommand();
    service.undoUserCommand();
    service.redoUserCommand();
    assert(service.getAdoptedDogs()[0].getName() == "Cooper");
    assert(service.getAdoptedDogs().size() == 1);

    service.undoUserCommand();
    service.undoUserCommand();
    assert(service.getAdoptedDogs()[0].getName() == "Daisy");
    assert(service.getAdoptedDogs().size() == 1);
    service.undoUserCommand();
    assert(service.getAdoptedDogs().empty());

    for(int i = 0; i < 4; i++)
        service.redoUserCommand();
    assert(service.getAdoptedDogs()[1].getName() == "Charlie");
    assert(service.getAdoptedDogs().size() == 2);

    admin_repository->clearFile();
    user_repository->clearFile();
}

void TestService::testFilter() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    service.add("Daisy", "Akita", "link", 3);
    service.add("Cooper", "Akita", "link", 1);
    service.add("Charlie", "Pug", "link", 2);
    service.filter("Akita", 3);

    // only one dog in the filtered list
    const Dog& dog1 = service.nextDog();
    assert(dog1.getName() == "Cooper");
    const Dog& dog2 = service.nextDog();
    assert(dog2.getName() == "Cooper");

    service.filter("Pug", 4);
    const  Dog& dog3 = service.nextDog();
    assert(dog3.getName() == "Charlie");

    service.filter("Pug", 1);
    try {
        service.nextDog();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dogs for this filtering!");
    }
    admin_repository->clearFile();
}

void TestService::testIsNegativeInteger() {
    const std::string& admin_file = "../files/sample.txt", user_file = "../files/sample.html";
    auto admin_repository = std::make_shared<FileRepository<Dog>>(admin_file);
    auto user_repository = std::make_shared<HTMLRepository<Dog>>(user_file);
    Service service(admin_repository, user_repository);

    assert(service.isNegativeInteger("-1") == true);
    assert(service.isNegativeInteger("-1324214") == true);
    assert(service.isNegativeInteger("-2") == true);
    assert(service.isNegativeInteger("2231") == false);
    assert(service.isNegativeInteger("923410") == false);
    assert(service.isNegativeInteger("00234") == false);
    assert(service.isNegativeInteger("0") == false);
    assert(service.isNegativeInteger("-0") == false);
    assert(service.isNegativeInteger("-01") == false);
    assert(service.isNegativeInteger("-0005") == false);
}