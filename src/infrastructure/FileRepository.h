#ifndef DOG_SHELTER_FILEREPOSITORY_H
#define DOG_SHELTER_FILEREPOSITORY_H
#include "Repository.h"
#include <fstream>

template <class T>
class FileRepository : public Repository<T> {
protected:
    void readFromFile();
    void writeToFile() override;
public:
    explicit FileRepository(const std::string& file_path);
    void update(const T& item, const T& newItem);
    T& operator[](int index);
};

template<class T>
FileRepository<T>::FileRepository(const std::string& file_path) : Repository<T>(file_path) {
    readFromFile();
}


template<class T>
void FileRepository<T>::update(const T &item, const T &newItem) {
    Repository<T>::remove(item);

    try {
        Repository<T>::add(newItem);
    }
    catch (const RepositoryException& e) {
        Repository<T>::add(item);
        throw RepositoryException("The new item already exists in the repository!");
    }
    writeToFile();
}

template<class T>
void FileRepository<T>::readFromFile() {
    std::ifstream file(Repository<T>::file_path);

    if(!file.is_open()) {
        throw RepositoryException("Cannot open " + Repository<T>::file_path + " file for reading!");
    }
    T item;
    while(file >> item)
        Repository<T>::add(item);
    file.close();
}

template <class T>
void FileRepository<T>::writeToFile() {
    std::ofstream file(Repository<T>::file_path);

    if(!file.is_open()) {
        throw RepositoryException("Cannot open " + Repository<T>::file_path + " file for writing!");
    }
    for(const auto& item : Repository<T>::items)
        file << item << '\n';
    file.close();
}

template<class T>
T& FileRepository<T>::operator[](int index) {
    return Repository<T>::items[index];
}
#endif //DOG_SHELTER_FILEREPOSITORY_H