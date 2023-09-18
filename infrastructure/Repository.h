#ifndef DOG_SHELTER_REPOSITORY_H
#define DOG_SHELTER_REPOSITORY_H
#include "../exceptions/RepositoryExeption.h"
#include <fstream>

template <class T>
class Repository {
protected:
    const std::string& file_path;
    std::vector<T> items;

    virtual void writeToFile() = 0;
public:
    explicit Repository(const std::string& file_path);
    void add(const T& item);
    void remove(const T& item);
    const std::vector<T>& getItems() const;
    int getIndex(const T& item) const;
    inline const std::string& getFilePath() { return file_path; }
    void clearFile();
private:
    typename std::vector<T>::iterator findItem(const T &item);
};

template<class T>
Repository<T>::Repository(const std::string& file_path) : file_path(file_path) {}

template<class T>
void Repository<T>::add(const T& item) {
    if(findItem(item) != items.end()) {
        throw RepositoryException("The provided item already exists in the repository!");
    }
    items.push_back(item);
    writeToFile();
}

template<class T>
void Repository<T>::remove(const T& item) {
    auto position = findItem(item);
    if(position == items.end()) {
        throw RepositoryException("Provided item not in repository!");
    }
    items.erase(position);
    writeToFile();
}

template<class T>
const std::vector<T>& Repository<T>::getItems() const {
    return items;
}

template<class T>
int Repository<T>::getIndex(const T& item) const {
    auto position = find(items.begin(), items.end(), item);

    if(position == items.end()) {
        throw RepositoryException("Item not found!");
    }
    return position - items.begin();
}

template<class T>
typename std::vector<T>::iterator Repository<T>::findItem(const T& item) {
    return find(items.begin(), items.end(), item);
}

template<class T>
void Repository<T>::clearFile() {
    std::ofstream file(Repository<T>::file_path);
    file.close();
}

#endif //DOG_SHELTER_REPOSITORY_H
