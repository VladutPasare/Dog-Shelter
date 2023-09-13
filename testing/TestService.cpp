#include "TestService.h"
#include "../exceptions/ServiceException.h"

TestService::TestService() {
    testAdd();
    testRemove();
    testUpdate();
    testNextDog();
    testUndoAdminCommand();
    testRedoAdminCommand();
    //testAddToAdoptionList();
    //testRemoveFromAdoptionList();
    /*testUndoUserCommand();
    testRedoUserCommand();*/
    testFilter();
    testIsNegativeInteger();
}

void TestService::testAdd() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    try {
        service.add("Cooper", "Akita", "Photo Link", -1);
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "Age cannot be negative!");
    }
    assert(service.getDogsFromShelter().empty());
    service.add("Cooper", "Akita", "Photo Link", 4);
    assert(service.getDogsFromShelter().size() == 1);
    assert(service.getDogsFromShelter()[0].getName() == "Cooper");
    assert(service.getDogsFromShelter()[0].getBreed() == "Akita");

    try {
        service.add("Cooper", "Akita", "Photo Link", 4);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    adminRepository->clearFile();
}

void TestService::testRemove() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Daisy", "Akita", "Photo Link", 2);
    assert(service.getDogsFromShelter().size() == 2);

    assert(service.getDogsFromShelter()[1].getName() == "Daisy");
    service.remove(0);
    assert(service.getDogsFromShelter().size() == 1);
    service.remove(0);
    assert(service.getDogsFromShelter().empty());

    adminRepository->clearFile();
}

void TestService::testUpdate() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Charlie", "Akita", "Photo Link", 4);

    service.update(0, "Daisy", "Akita", "Photo Link", 4);
    assert(service.getDogsFromShelter()[1].getName() == "Daisy");
    assert(service.getDogsFromShelter().size() == 2);

    try {
        service.update(1, "Charlie", "Akita", "Photo Link", 4);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "The new item already exists in the repository!");
    }
    adminRepository->clearFile();
}

void TestService::testNextDog() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    try {
        service.filter("", -1);
        const Dog& dog = service.nextDog();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dogs for this filtering!");
    }

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Daisy", "Akita", "Photo Link", 2);

    service.filter("", -1);
    const Dog& dog1 = service.nextDog();
    assert(dog1.getName() == "Cooper");
    const Dog& dog2 = service.nextDog();
    assert(dog2.getName() == "Daisy");
    const Dog& dog3 = service.nextDog();
    assert(dog3 == dog1);

    adminRepository->clearFile();
}

void TestService::testUndoAdminCommand() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 3);
    service.add("Cooper", "Akita", "Photo Link", 1);
    service.remove(0);

    service.update(0, "Cooper", "Akita", "Photo Link", 5);

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
    adminRepository->clearFile();
}

void TestService::testRedoAdminCommand() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 3);
    service.remove(0);
    service.add("Cooper", "Akita", "Photo Link", 1);

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

    service.update(0, "Charlie", "Akita", "Photo Link", 3);
    assert(service.getDogsFromShelter()[0].getName() == "Charlie");
    service.undoAdminCommand();
    assert(service.getDogsFromShelter()[0].getName() == "Daisy");
    service.redoAdminCommand();
    assert(service.getDogsFromShelter()[0].getName() == "Charlie");
    adminRepository->clearFile();
}

void TestService::testAddToAdoptionList() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Daisy", "Akita", "Photo Link", 2);

    Dog d1("Cooper", "Akita", "Photo Link", 4);
    Dog d2("Daisy", "Akita", "Photo Link", 2);
    assert(service.getAdoptedDogs().empty());
    //service.addToAdoptionList(d1);
    //assert(service.getAdoptedDogs().size() == 1);
/*
    service.addToAdoptionList(d2);
    assert(service.getAdoptedDogs()[0].getName() == "Cooper");

    try {
        service.addToAdoptionList(d1);
        assert(false);
    }
    catch (const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    adminRepository->clearFile();*/
}
/*
void TestService::testRemoveFromAdoptionList() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);

    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Daisy", "Akita", "Photo Link", 2);
    Dog d1("Cooper", "Akita", "Photo Link", 4);
    Dog d2("Daisy", "Akita", "Photo Link", 2);

    service.addToAdoptionList(d1);
    service.addToAdoptionList(d2);

   Dog dog("Charlie", "Akita", "Photo Link", 5);
   try {
       service.removeFromAdoptionList(dog);
       assert(false);
   }
   catch (const RepositoryException& e) {
       assert(e.getErrorMessage() == "Provided item not in repository!");
   }
   dog.setName("Daisy");
   service.removeFromAdoptionList(dog);
   assert(service.getAdoptedDogs().size() == 1);
   assert(service.getAdoptedDogs()[0].getName() == "Cooper");
   dog.setName("Cooper");
   service.removeFromAdoptionList(dog);
   assert(service.getAdoptedDogs().empty());
   // dogs added back to admin repo
   assert(service.getDogsFromShelter()[0].getName() == "Daisy");
   assert(service.getDogsFromShelter()[1].getName() == "Cooper");
   assert(service.getDogsFromShelter().size() == 2);

    adminRepository->clearFile();
}

void TestService::testUndoUserCommand() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 1);
    service.add("Cooper", "Akita", "Photo Link", 1);

    service.addToAdoptionList(Dog("Daisy", "Akita", "Photo Link", 1));
    service.addToAdoptionList(Dog("Cooper", "Akita", "Photo Link", 1));
    service.removeFromAdoptionList(Dog("Cooper", "Akita", "Photo Link", 1));
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
}

void TestService::testRedoUserCommand() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 1);
    service.add("Cooper", "Akita", "Photo Link", 1);
    service.add("Charlie", "Akita", "Photo Link", 2);

    service.addToAdoptionList(Dog("Daisy", "Akita", "Photo Link", 1));
    service.removeFromAdoptionList(Dog("Daisy", "Akita", "Photo Link", 1));
    service.addToAdoptionList(Dog("Cooper", "Akita", "Photo Link", 1));
    service.addToAdoptionList(Dog("Charlie", "Akita", "Photo Link", 2));

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
}
*/
void TestService::testFilter() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 3);
    service.add("Cooper", "Akita", "Photo Link", 1);
    service.add("Charlie", "none", "Photo Link", 2);
    service.filter("Akita", 3);

    // only one dog in the filtered list
    const Dog& dog1 = service.nextDog();
    assert(dog1.getName() == "Cooper");
    const Dog& dog2 = service.nextDog();
    assert(dog2.getName() == "Cooper");

    service.filter("none", 4);
    const  Dog& dog3 = service.nextDog();
    assert(dog3.getName() == "Charlie");

    service.filter("none", 1);
    try {
        service.nextDog();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dogs for this filtering!");
    }

    adminRepository->clearFile();
}

void TestService::testIsNegativeInteger() {
    const std::string& adminFile = "../files/sample.txt", userFile = "../files/sample.html";
    auto adminRepository = std::make_shared<FileRepository<Dog>>(adminFile);
    auto userRepository = std::make_shared<HTMLRepository<Dog>>(userFile);
    Service service(adminRepository, userRepository);

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
