#include "ServiceException.h"

ServiceException::ServiceException(const std::string &errorMessage) {
    this->message = errorMessage;
}

const std::string &ServiceException::getErrorMessage() const{
    return this->message;
}
