#ifndef KEEP_CALM_AND_ADOPT_A_PET_SERVICEEXCEPTION_H
#define KEEP_CALM_AND_ADOPT_A_PET_SERVICEEXCEPTION_H
#include <exception>
#include <string>

class ServiceException : public std::exception {
private:
    std::string message;
public:
    explicit ServiceException(const std::string& errorMessage);
    const std::string& getErrorMessage() const;
};
#endif //KEEP_CALM_AND_ADOPT_A_PET_SERVICEEXCEPTION_H
