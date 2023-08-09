#include "TestUserHTMLRepository.h"

TestUserHTMLRepository::TestUserHTMLRepository() {
    testAdd();
    testRemove();
}

void TestUserHTMLRepository::testAdd() {
    UserHTMLRepository<Dog> userRepository("sample.html");

    Dog dog("Cooper", "Akita", "Photo Link", 4);
    userRepository.add(dog);
    assert(userRepository.getItems().size() == 1);
    assert(userRepository.getItems()[0] == dog);
    try{
        userRepository.add(dog);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the user's repository!");
    }
}

void TestUserHTMLRepository::testRemove() {
    UserHTMLRepository<Dog> userRepository("sample.html");

    Dog dog("Cooper", "Akita", "Photo Link", 4);
    userRepository.add(dog);

    assert(userRepository.getItems()[0] == dog);
    Dog new_dog("Daisy", "Akita", "Photo Link", 2);
    try {
        userRepository.remove(new_dog);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item not in user's repository!");
    }
    assert(userRepository.getItems().size() == 1);
}
