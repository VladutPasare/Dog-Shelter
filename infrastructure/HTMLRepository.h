#ifndef DOG_SHELTER_HTMLREPOSITORY_H
#define DOG_SHELTER_HTMLREPOSITORY_H
#include "Repository.h"
#include <fstream>

template <class T>
class HTMLRepository : public Repository<T> {
protected:
    void writeToFile() override;
public:
    explicit HTMLRepository(const std::string& file_path);
};

template<class T>
HTMLRepository<T>::HTMLRepository(const std::string& file_path) : Repository<T>(file_path) {}


template<class T>
void HTMLRepository<T>::writeToFile() {
    std::ofstream file(Repository<T>::file_path);
    if(!file.is_open()) {
        throw RepositoryException("Cannot open " + Repository<T>::file_path + " file for writing");
    }

    file << "<!DOCTYPE html>  \n"
            "<html> \n"
            "<head> \n"
            "    <title>Dog Shelter</title>\n"
            "</head> \n"
            "<body> \n"
            "<table border=\"1\"> \n";
    file << "<tr>         \n"
            "        <td>Name</td>\n"
            "           <td>Breed</td>\n"
            "        <td>Age</td>\n"
            "        <td>Link</td>\n"
            "</td>";

    for(const T &item : Repository<T>::items)
        file << item.toHTMLFormat();

    file << "</tr>\n"
            "</table>\n"
            "</body>\n"
            "</html>";
    file.close();
}
#endif //DOG_SHELTER_HTMLREPOSITORY_H
