#ifndef KEEP_CALM_AND_ADOPT_A_PET_DOGVALIDATOR_H
#define KEEP_CALM_AND_ADOPT_A_PET_DOGVALIDATOR_H
#include "../domain/Dog.h"

class DogValidator {
private:
    std::string error_message;
public:
    bool validate(const Dog& dog);
    inline std::string getErrorMessage() const { return error_message; }
};
#endif //KEEP_CALM_AND_ADOPT_A_PET_DOGVALIDATOR_H
