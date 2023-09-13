#include "TestHTMLRepository.h"

TestHTMLRepository::TestHTMLRepository() {
    testAdd();
    testRemove();
}

void TestHTMLRepository::testAdd() {
    HTMLRepository<Dog> htmlRepository("../files/sample.html");

    Dog dog("Cooper", "Akita", "Photo Link", 4);
    htmlRepository.add(dog);
    assert(htmlRepository.getItems().size() == 1);
    assert(htmlRepository.getItems()[0] == dog);
    try{
        htmlRepository.add(dog);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }
}

void TestHTMLRepository::testRemove() {
    HTMLRepository<Dog> userRepository("../files/sample.html");

    Dog dog("Cooper", "Akita", "Photo Link", 4);
    userRepository.add(dog);

    assert(userRepository.getItems()[0] == dog);
    Dog new_dog("Daisy", "Akita", "Photo Link", 2);
    try {
        userRepository.remove(new_dog);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }
    assert(userRepository.getItems().size() == 1);
}
