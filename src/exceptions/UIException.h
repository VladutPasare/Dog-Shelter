#ifndef DOG_SHELTER_UIEXCEPTION_H
#define DOG_SHELTER_UIEXCEPTION_H
#include "Exception.h"
#include <string>

class UIException : public Exception {
private:
    std::string message;
public:
    explicit UIException(const std::string& errorMessage) : Exception(errorMessage) {}
};

#endif //DOG_SHELTER_UIEXCEPTION_H
