#include "DogValidator.h"

bool DogValidator::validate(const Dog &dog) {
    error_message = "";
    if(dog.getAge() < 0)
        error_message = "Age cannot be negative!";
    return error_message.empty();
    // verifica si pentru breedField="" sau nameField sau photolink
}
