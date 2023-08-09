#include "UIException.h"

UIException::UIException(const std::string& errorMessage) {
    this->message = errorMessage;
}

const std::string &UIException::getErrorMessage() const{
    return this->message;
}
