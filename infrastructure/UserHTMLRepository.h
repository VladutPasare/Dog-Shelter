#ifndef KEEP_CALM_AND_ADOPT_A_PET_USERHTMLREPOSITORY_H
#define KEEP_CALM_AND_ADOPT_A_PET_USERHTMLREPOSITORY_H
#include "UserRepository.h"
#include <fstream>

template <class T>
class UserHTMLRepository : public UserRepository<T> {
private:
    const std::string& filePath;
public:
    explicit UserHTMLRepository(const std::string& filePath);
    void add(const T& item) override;
    void remove(const T& item) override;
    void writeToHTMLFile();
};

template<class T>
UserHTMLRepository<T>::UserHTMLRepository(const std::string& filePath) : filePath(filePath) {

}

template<class T>
void UserHTMLRepository<T>::add(const T &item) {
    if(UserRepository<T>::findItem(item) != UserRepository<T>::items.end())
        throw RepositoryException("The provided item already exists in the user's repository!");
    UserRepository<T>::items.push_back(item);
    writeToHTMLFile();
}

template<class T>
void UserHTMLRepository<T>::remove(const T &item) {
    auto position = UserRepository<T>::findItem(item);
    if(position == UserRepository<T>::items.end())
        throw RepositoryException("The provided item not in user's repository!");
    UserRepository<T>::items.erase(position);
    writeToHTMLFile();
}



template<class T>
void UserHTMLRepository<T>::writeToHTMLFile() {
    std::ofstream file(filePath);
    file << "<!DOCTYPE html>  \n"
            "<html> \n"
            "<head> \n"
            "    <title>Dog Shelter</title>\n"
            "</head> \n"
            "<body> \n"
            "<table border=\"1\"> ";
    file << "<tr>         \n"
            "        <td>Name</td> \n"
            "           <td>Breed</td>\n"
            "        <td>Photo link</td>\n"
            "        <td>Age</td>\n"
            "</td>";

    for(const T &item : UserRepository<T>::items)
        file << item.toHTMLFormat();

    file << "</tr>\n"
            "</table>\n"
            "</body>\n"
            "</html>";
}
#endif //KEEP_CALM_AND_ADOPT_A_PET_USERHTMLREPOSITORY_H
