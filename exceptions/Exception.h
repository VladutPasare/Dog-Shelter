#ifndef DOG_SHELTER_EXCEPTION_H
#define DOG_SHELTER_EXCEPTION_H
#include <string>
#include <exception>
#include <utility>

class Exception : std::exception {
protected:
    std::string message;
public:
    explicit Exception(std::string  errorMessage) : message(std::move(errorMessage)) {}
    inline const std::string& getErrorMessage() const { return message; }
};

#endif //DOG_SHELTER_EXCEPTION_H
