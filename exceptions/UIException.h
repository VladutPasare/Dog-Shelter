#ifndef KEEP_CALM_AND_ADOPT_A_PET_UIEXCEPTION_H
#define KEEP_CALM_AND_ADOPT_A_PET_UIEXCEPTION_H
#include "exception"
#include <string>

class UIException : public std::exception {
private:
    std::string message;
public:
    explicit UIException(const std::string& errorMessage);
    const std::string& getErrorMessage() const;
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_UIEXCEPTION_H
