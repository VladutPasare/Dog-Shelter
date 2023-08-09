#include "TestService.h"
#include "../exceptions/ServiceException.h"

TestService::TestService() {
    testAdd();
    testRemove();
    testNextDog();
    testAddToAdoptionList();
    testRemoveFromAdoptionList();
    testFilter();
    testNextDogInFilteredList();
    testAddToAdoptionListFromFilteredList();
    testIsNegativeInteger();
}

void TestService::testAdd() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
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
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    adminRepository.clearFile();
}

void TestService::testRemove() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);

    assert(service.getDogsFromShelter().size() == 1);
    try {
        service.remove("Daisy", "Akita");
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "Item not found!");
    }

    service.add("Daisy", "Akita", "Photo Link", 2);
    assert(service.getDogsFromShelter().size() == 2);
    assert(service.getDogsFromShelter()[1].getName() == "Daisy");
    service.remove("Cooper", "Akita");
    assert(service.getDogsFromShelter().size() == 1);
    service.remove("Daisy", "Akita");
    assert(service.getDogsFromShelter().empty());

    adminRepository.clearFile();
}

void TestService::testUpdate() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);
    try {
        service.update("Cooper", "Akita", "Cooper", "Akita", "Photo Link", 4);
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "The new item already exists in the repository!");
    }
    try {
        service.update("Max", "Akita", "Daisy", "Akita", "Photo Link", 4);
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "Item not found!");
    }
    service.update("Cooper", "Akita", "Daisy", "Akita", "Photo Link", 4);
    assert(service.getDogsFromShelter()[0].getName() == "Daisy");
    assert(service.getDogsFromShelter().size() == 1);

    adminRepository.clearFile();
}

void TestService::testNextDog() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    try {
        const Dog& dog = service.nextDog();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dog in shelter!");
    }

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Daisy", "Akita", "Photo Link", 2);

    const Dog& dog1 = service.nextDog();
    assert(dog1.getName() == "Cooper");
    const Dog& dog2 = service.nextDog();
    assert(dog2.getName() == "Daisy");
    const Dog& dog3 = service.nextDog();
    assert(dog3 == dog1);

    adminRepository.clearFile();
}

void TestService::testAddToAdoptionList() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    service.add("Cooper", "Akita", "Photo Link", 4);
    service.add("Daisy", "Akita", "Photo Link", 2);

    Dog d1("Cooper", "Akita", "Photo Link", 4);
    Dog d2("Daisy", "Akita", "Photo Link", 2);
    assert(service.getAdoptedDogs().empty());
    service.addToAdoptionList(d1);
    assert(service.getAdoptedDogs().size() == 1);

    service.addToAdoptionList(d2);
    assert(service.getAdoptedDogs()[0].getName() == "Cooper");

    try {
        service.addToAdoptionList(d1);
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the user's repository!");
    }

    adminRepository.clearFile();
}

void TestService::testRemoveFromAdoptionList() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
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
   catch (const ServiceException& e) {
       assert(e.getErrorMessage() == "The provided item not in user's repository!");
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

    adminRepository.clearFile();
}

void TestService::testFilter() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 3);
    service.add("Cooper", "Akita", "Photo Link", 1);
    service.add("Charlie", "none", "Photo Link", 2);
    service.filter("Akita", 3);

    // only one dog in the filtered list
    const Dog& dog1 = service.nextDogInFilteredList();
    assert(dog1.getName() == "Cooper");
    const Dog& dog2 = service.nextDogInFilteredList();
    assert(dog2.getName() == "Cooper");

    service.filter("none", 4);
    const  Dog& dog3 = service.nextDogInFilteredList();
    assert(dog3.getName() == "Charlie");

    service.filter("none", 1);
    try {
        service.nextDogInFilteredList();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dogs for this filtering!");
    }

    adminRepository.clearFile();
}

void TestService::testNextDogInFilteredList() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    try {
        Dog dog = service.nextDogInFilteredList();
        assert(false);
    }
    catch (const ServiceException& e) {
        assert(e.getErrorMessage() == "No dogs for this filtering!");
    }
    service.add("Daisy", "Akita", "none", 1);
    service.add("Cooper", "Akita", "none", 2);

    service.filter("Akita", 5);
    assert(service.nextDogInFilteredList().getName() == "Daisy");
    assert(service.nextDogInFilteredList().getName() == "Cooper");
    assert(service.nextDogInFilteredList().getName() == "Daisy");

    adminRepository.clearFile();
}

void TestService::testAddToAdoptionListFromFilteredList() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
    Service service(adminRepository, userRepository);

    service.add("Daisy", "Akita", "Photo Link", 3);
    service.add("Cooper", "Akita", "Photo Link", 1);
    service.add("Charlie", "none", "Photo Link", 2);

    assert(service.getDogsFromShelter().size() == 3);

    service.filter("Akita", 10);
    Dog dog = service.nextDogInFilteredList();

    service.addToAdoptionListFromFilteredList(dog);

    try {
        service.addToAdoptionListFromFilteredList(dog);
        assert(false);
    }
    catch(ServiceException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the user's repository!");
    }

    adminRepository.clearFile();
}

void TestService::testIsNegativeInteger() {
    AdminRepository<Dog> adminRepository("sample.txt");
    UserHTMLRepository<Dog> userHtmlRepository("sample.html");
    UserRepository<Dog>* userRepository = &userHtmlRepository;
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