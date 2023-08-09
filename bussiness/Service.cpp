#include "Service.h"
#include "../exceptions/ServiceException.h"


void Service::add(const std::string &name, const std::string &breed, const std::string& photo_link, int age) {
    Dog dog(name, breed, photo_link, age);

    if(!dog_validator.validate(dog)) {
        throw ServiceException(dog_validator.getErrorMessage());
    }

    try {
        admin_repo.add(dog);
    }
    catch(const RepositoryException& exception){
            throw ServiceException(exception.getErrorMessage());
    }
}

void Service::remove(const std::string &name, const std::string &breed) {
    Dog dog(name, breed, "", 0);

    try {
        int index = admin_repo.getIndex(dog);
        admin_repo.remove(dog);
    }
    catch(const RepositoryException& exception){
        throw ServiceException(exception.getErrorMessage());
    }
}

void Service::update(const std::string &name, const std::string &breed, const std::string &new_name, const std::string& new_breed,
                const std::string &new_photo_link, int new_age) {
    Dog dog(name, breed, "", 0);

    try {
        Dog new_dog(new_name, new_breed, new_photo_link, new_age);
        admin_repo.update(dog, new_dog);
    }
    catch (const RepositoryException& exception) {
        throw ServiceException(exception.getErrorMessage());
    }
}

std::vector<Dog> Service::getDogsFromShelter() const {
    return admin_repo.getItems();
}

const Dog& Service::nextDog() {
    if(admin_repo.getItems().empty())
        throw ServiceException("No dog in shelter!");

    if(current_dog_position == admin_repo.getItems().size() - 1)
        current_dog_position = 0;
    else
        current_dog_position++;
    return admin_repo[current_dog_position];
}

void Service::addToAdoptionList(const Dog& dog) {
    try {
        user_repo->add(dog);
        admin_repo.remove(dog);
    }
    catch(const RepositoryException& exception) {
        throw ServiceException(exception.getErrorMessage());
    }
}

void Service::removeFromAdoptionList(const Dog& dog) {
    try {
        user_repo->remove(dog);
        admin_repo.add(dog);
    }
    catch (const RepositoryException& exception) {
        throw ServiceException(exception.getErrorMessage());
    }
}
std::vector<Dog> Service::getAdoptedDogs() const {
    return user_repo->getItems();
}

void Service::filter(const std::string &breed, int max_age) {
    filtered_list.clear();
    current_dog_position_in_filtered_list = -1;
    std::vector<Dog> dogs = admin_repo.getItems();

    std::copy_if(dogs.begin(), dogs.end(), std::back_inserter(filtered_list),
                 [&] (Dog& dog){
                return dog.getBreed() == breed && dog.getAge() < max_age;
    });
}

const Dog &Service::nextDogInFilteredList() {
    if(filtered_list.empty())
        throw ServiceException("No dogs for this filtering!");
    if(current_dog_position_in_filtered_list == filtered_list.size() - 1)
        current_dog_position_in_filtered_list = 0;
    else
        current_dog_position_in_filtered_list ++;
    return filtered_list[current_dog_position_in_filtered_list];
}

void Service::addToAdoptionListFromFilteredList(const Dog& dog) {
    try{
        user_repo->add(dog);
        admin_repo.remove(dog);
        auto position = std::find(filtered_list.begin(), filtered_list.end(), dog);
        filtered_list.erase(position);
    }
    catch (const RepositoryException& exception) {
        throw ServiceException(exception.getErrorMessage());
    }
};

bool Service::isNegativeInteger(const std::string& number) {
    if(number.size() < 2 || number[0] != '-' || number[1] == '0')
        return false;

    return std::all_of(number.begin() + 1, number.end(), [] (char c) { return isdigit(c); });
}