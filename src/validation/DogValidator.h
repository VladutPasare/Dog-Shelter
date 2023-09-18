#ifndef DOG_SHELTER_DOGVALIDATOR_H
#define DOG_SHELTER_DOGVALIDATOR_H
#include "../domain/Dog.h"

class DogValidator {
private:
    std::string error_message;
public:
    bool validate(const Dog& dog);
    inline std::string getErrorMessage() const { return error_message; }
};
#endif //DOG_SHELTER_DOGVALIDATOR_H
