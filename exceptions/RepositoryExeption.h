#ifndef KEEP_CALM_AND_ADOPT_A_PET_REPOSITORYEXEPTION_H
#define KEEP_CALM_AND_ADOPT_A_PET_REPOSITORYEXEPTION_H
#include <exception>
#include <string>

class RepositoryException : public std::exception {
private:
    std::string message;
public:
    explicit RepositoryException(const std::string &errorMessage);
    const std::string& getErrorMessage() const;
};
#endif //KEEP_CALM_AND_ADOPT_A_PET_REPOSITORYEXEPTION_H
