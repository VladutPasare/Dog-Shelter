#ifndef KEEP_CALM_AND_ADOPT_A_PET_USERREPOSITORY_H
#define KEEP_CALM_AND_ADOPT_A_PET_USERREPOSITORY_H

#include "../exceptions/RepositoryExeption.h"
#include <vector>
#include <algorithm>

template <class T>
class UserRepository {
protected:
    std::vector<T> items;
public:
    virtual void add(const T& item) = 0;
    virtual void remove(const T& item) = 0;
    typename std::vector<T>::iterator findItem(const T &item);
    std::vector<T> getItems() const;
};

template<class T>
std::vector<T> UserRepository<T>::getItems() const {
    return items;
}

template<class T>
typename std::vector<T>::iterator UserRepository<T>::findItem(const T &item) {
    return find(items.begin(), items.end(), item);
}
#endif //KEEP_CALM_AND_ADOPT_A_PET_USERREPOSITORY_H
