#include "TestValidation.h"
#include "../validation/DogValidator.h"

TestValidation::TestValidation() {
    testDogValidator();
}

void TestValidation::testDogValidator() {
    DogValidator dogValidator;

    Dog dog("", "Akita", "www.google.com", 2);

    assert(dogValidator.validate(dog) == false);
    assert(dogValidator.getErrorMessage() == "Invalid name!");

    dog = Dog("Charlie", "", "", 0);

    assert(dogValidator.validate(dog) == false);
    assert(dogValidator.getErrorMessage() == "Invalid breed!");

    dog = Dog("Charlie", "Akita", "", 0);

    assert(dogValidator.validate(dog) == false);
    assert(dogValidator.getErrorMessage() == "Invalid link!");

    dog = Dog("Charlie", "Akita", "www.google.com", 0);

    assert(dogValidator.validate(dog) == false);
    assert(dogValidator.getErrorMessage() == "Invalid age!");

    dog = Dog("Charlie", "Akita", "www.google.com", 1);

    assert(dogValidator.validate(dog) == true);
}
