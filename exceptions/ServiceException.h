#ifndef DOG_SHELTER_SERVICEEXCEPTION_H
#define DOG_SHELTER_SERVICEEXCEPTION_H
#include "Exception.h"
#include <string>

class ServiceException : public Exception {
private:
    std::string message;
public:
    explicit ServiceException(const std::string& errorMessage) : Exception(errorMessage) {}
};
#endif //DOG_SHELTER_SERVICEEXCEPTION_H
