#include "DogValidator.h"

bool DogValidator::validate(const Dog &dog) {
    error_message = "";

    if (dog.getName().empty()) {
        error_message = "Invalid name!";
        return false;
    }

    if (dog.getBreed().empty()) {
        error_message = "Invalid breed!";
        return false;
    }

    if (dog.getLink().empty()) {
        error_message = "Invalid link!";
        return false;
    }

    if(!dog.getAge()) {
        error_message = "Invalid age!";
        return false;
    }
    return true;
}
