#include "RepositoryExeption.h"

RepositoryException::RepositoryException(const std::string &errorMessage) : std::exception(){
    this->message = errorMessage;
}

const std::string &RepositoryException::getErrorMessage() const {
    return this->message;
}
