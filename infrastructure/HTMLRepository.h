#ifndef DOG_SHELTER_HTMLREPOSITORY_H
#define DOG_SHELTER_HTMLREPOSITORY_H
#include "Repository.h"
#include <fstream>

template <class T>
class HTMLRepository : public Repository<T> {
public:
    explicit HTMLRepository(const std::string& filePath);
    void add(const T& item) override;
    void remove(const T& item) override;
    void writeToFile();
};

template<class T>
HTMLRepository<T>::HTMLRepository(const std::string& filePath) : Repository<T>(filePath) {}

template<class T>
void HTMLRepository<T>::add(const T &item) {
    Repository<T>::add(item);
    writeToFile();
}

template<class T>
void HTMLRepository<T>::remove(const T &item) {
    Repository<T>::remove(item);
    writeToFile();
}

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
            "<table border=\"1\"> ";
    file << "<tr>         \n"
            "        <td>Name</td> \n"
            "           <td>Breed</td>\n"
            "        <td>Photo linkField</td>\n"
            "        <td>Age</td>\n"
            "</td>";

    for(const T &item : Repository<T>::items)
        file << item.toHTMLFormat();

    file << "</tr>\n"
            "</table>\n"
            "</body>\n"
            "</html>";
}
#endif //DOG_SHELTER_HTMLREPOSITORY_H
