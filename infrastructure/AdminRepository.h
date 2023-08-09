#ifndef KEEP_CALM_AND_ADOPT_A_PET_ADMINREPOSITORY_H
#define KEEP_CALM_AND_ADOPT_A_PET_ADMINREPOSITORY_H
#include "../domain/Dog.h"
#include "../exceptions/RepositoryExeption.h"
#include <vector>
#include <fstream>

template <class T>
class AdminRepository {
private:
    std::vector <T> items;
    const std::string& filePath;

    void readFromFile();
    void writeToFile();
public:
    explicit AdminRepository(const std::string& filePath);
    void add(const T& item);
    void remove(const T& item);
    void update(const T& item, const T& new_item);
    std::vector<T> getItems() const;
    int getIndex(const T& item) const;
    T& operator[](int index);
    void clearFile();
};

template<class T>
AdminRepository<T>::AdminRepository(const std::string& filePath) : filePath(filePath) {
    readFromFile();
}

template<class T>
void AdminRepository<T>::add(const T &item) {

    if(find(items.begin(), items.end(), item) != items.end()) {
        throw RepositoryException("The provided item already exists in the repository!");
    }
    items.push_back(item);
    writeToFile();
}


template<class T>
void AdminRepository<T>::remove(const T &item) {
    // repository error thrown by getIndex function when the element is not found
    items.erase(items.begin() + getIndex(item));
    writeToFile();
}

template<class T>
void AdminRepository<T>::update(const T &item, const T &new_item) {
    // repository error thrown by getIndex function when the element is not found
    T& oldItem = items[getIndex(item)];

    if(find(items.begin(), items.end(), new_item) != items.end()) {
        throw RepositoryException( "The new item already exists in the repository!");
    }
    oldItem = new_item;
    writeToFile();
}

template<class T>
std::vector<T> AdminRepository<T>::getItems() const {
    return items;
}

template<class T>
int AdminRepository<T>::getIndex(const T &item) const {
    auto position = find(items.begin(), items.end(), item);

    if(position == items.end()) {
        throw RepositoryException("Item not found!");
    }
    return position - items.begin();
}

template<class T>
void AdminRepository<T>::readFromFile() {

    std::ifstream file(filePath);
    if(!file.is_open()) {
        throw RepositoryException("Cannot open " + filePath + " filePath for reading!");
    }
    T item;
    while(file >> item)
        add(item);
    file.close();
}

template <class T>
void AdminRepository<T>::writeToFile() {
    std::ofstream file(filePath);

    if(!file.is_open()) {
        throw RepositoryException("Cannot open " + filePath + " filePath for writing!");
    }
    for(const auto& item : items)
        file << item << '\n';
    file.close();
}

template<class T>
T& AdminRepository<T>::operator[](int index) {
    return items[index];
}

template<class T>
void AdminRepository<T>::clearFile() {
    //std::ofstream file;
    //file.open(filePath, std::ios::out | std::ofstream::trunc);
    //file.close();
    std::ofstream g(filePath, std::ios::trunc);
    g.close();
}
#endif //KEEP_CALM_AND_ADOPT_A_PET_ADMINREPOSITORY_H
