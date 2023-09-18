#ifndef DOG_SHELTER_REPOSITORYEXEPTION_H
#define DOG_SHELTER_REPOSITORYEXEPTION_H
#include "Exception.h"
#include <string>

class RepositoryException : public Exception {
private:
    std::string message;
public:
    explicit RepositoryException(const std::string &errorMessage) : Exception(errorMessage) {}
};
#endif //DOG_SHELTER_REPOSITORYEXEPTION_H
