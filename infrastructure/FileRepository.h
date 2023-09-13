#ifndef DOG_SHELTER_FILEREPOSITORY_H
#define DOG_SHELTER_FILEREPOSITORY_H
#include "Repository.h"
#include <fstream>

template <class T>
class FileRepository : public Repository<T> {
private:
    void readFromFile();
    void writeToFile();
public:
    explicit FileRepository(const std::string& file_path);
    void add(const T& item) override;
    void remove(const T& item) override;
    void update(const T& item, const T& newItem) override;
    T& operator[](int index);
    void clearFile();
};

template<class T>
FileRepository<T>::FileRepository(const std::string& file_path) : Repository<T>(file_path) {
    readFromFile();
}

template<class T>
void FileRepository<T>::add(const T &item) {
    Repository<T>::add(item);
    writeToFile();
}


template<class T>
void FileRepository<T>::remove(const T &item) {
    Repository<T>::remove(item);
    writeToFile();
}

template<class T>
void FileRepository<T>::update(const T &item, const T &newItem) {
    Repository<T>::update(item, newItem);
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
        add(item);
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

template<class T>
void FileRepository<T>::clearFile() {
    std::ofstream file(Repository<T>::file_path);
    file.close();
}
#endif //DOG_SHELTER_FILEREPOSITORY_H