#ifndef DOG_SHELTER_CSVREPOSITORY_H
#define DOG_SHELTER_CSVREPOSITORY_H
#include "Repository.h"
#include <fstream>

template <class T>
class CSVRepository : public Repository<T> {
protected:
    void writeToFile() override;
public:
    explicit CSVRepository(const std::string& file_path);
};

template<class T>
CSVRepository<T>::CSVRepository(const std::string &file_path): Repository<T>(file_path) {}

template<class T>
void CSVRepository<T>::writeToFile() {
    std::ofstream file(Repository<T>::file_path);

    if(!file.is_open())
        throw RepositoryException("Cannot open " + Repository<T>::file_path + " file for writing");

    for(const T &item : Repository<T>::items)
        file << item.toCSVFormat() << '\n';
    file.close();
}
#endif //DOG_SHELTER_CSVREPOSITORY_H
