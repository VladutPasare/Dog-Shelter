#include "Service.h"
#include <utility>
#include "../exceptions/ServiceException.h"
#include <memory>

Service::Service(std::shared_ptr<FileRepository<Dog>> admin_repo, std::shared_ptr<Repository<Dog>> user_repository) : admin_repo(std::move(admin_repo)), user_repo(std::move(user_repository)) {}

void Service::add(const std::string &name, const std::string &breed, const std::string& photo_link, int age) {
    Dog dog(name, breed, photo_link, age);

    if(!dog_validator.validate(dog)) {
        throw ServiceException(dog_validator.getErrorMessage());
    }
    admin_repo->add(dog);

    std::unique_ptr<Command> currentCommand = std::make_unique<AdminCommandAdd>(dog, admin_repo);
    admin_undo_commands.push(std::move(currentCommand));

    while(!admin_redo_commands.empty())
        admin_redo_commands.pop();
}

void Service::remove(int index) {
    Dog dog = admin_repo->getItems()[index];

    admin_repo->remove(dog);
    std::unique_ptr<Command> currentCommand = std::make_unique<AdminCommandRemove>(dog, admin_repo);
    admin_undo_commands.push(std::move(currentCommand));

    while(!admin_redo_commands.empty())
        admin_redo_commands.pop();
}

void Service::update(int index, const std::string &new_name, const std::string& new_breed,
                const std::string &new_photo_link, int new_age) {

    Dog dog = admin_repo->getItems()[index];
    Dog new_dog(new_name, new_breed, new_photo_link, new_age);

    if(!dog_validator.validate(new_dog)) {
        throw ServiceException(dog_validator.getErrorMessage());
    }
    admin_repo->update(dog, new_dog);

    std::unique_ptr<Command> currentCommand = std::make_unique<AdminCommandUpdate>(dog, new_dog, admin_repo);
    admin_undo_commands.push(std::move(currentCommand));

    while(!admin_redo_commands.empty())
        admin_redo_commands.pop();
}

const std::vector<Dog>& Service::getDogsFromShelter() const {
    return admin_repo->getItems();
}

std::set<std::string> Service::getDogBreeds() {
    std::set<std::string> dogBreeds;
    const std::vector<Dog> dogs = getDogsFromShelter();

    for(const Dog& dog : dogs)
        dogBreeds.insert(dog.getBreed());

    return dogBreeds;
}

unsigned int Service::countDogsByBreed(const std::string &breed) const {
    const std::vector<Dog> dogs = getDogsFromShelter();
    return std::count_if(dogs.begin(), dogs.end(), [&] (const Dog& dog) {
        return dog.getBreed() == breed;
    });
}

void Service::undoAdminCommand() {
    if(admin_undo_commands.empty())
        throw ServiceException("Cannot undo!");
    std::unique_ptr<Command> command = std::move(admin_undo_commands.top());
    admin_undo_commands.pop();
    command->undo();
    admin_redo_commands.push(std::move(command));
}

void Service::redoAdminCommand() {
    if(admin_redo_commands.empty())
        throw ServiceException("Cannot redo!");
    std::unique_ptr<Command> command = std::move(admin_redo_commands.top());
    admin_redo_commands.pop();
    command->redo();
    admin_undo_commands.push(std::move(command));
}

void Service::reset_filtered_list() {
    //filtered_list.clear();
    filtered_list = admin_repo->getItems();
}

void Service::filter(const std::string &breed, int max_age) {
    filtered_list.clear();
    std::vector<Dog> dogs = admin_repo->getItems();
    current_dog_position = -1;

    if(breed.empty())
        std::copy_if(dogs.begin(), dogs.end(), std::back_inserter(filtered_list),[&] (Dog& dog){
            return dog.getAge() < max_age;
        });
    else
        std::copy_if(dogs.begin(), dogs.end(), std::back_inserter(filtered_list),[&] (Dog& dog){
                    return dog.getBreed() == breed && dog.getAge() < max_age;
        });
}

const Dog &Service::nextDog() {
    if(filtered_list.empty())
        throw ServiceException("No dogs for this filtering!");

    if(current_dog_position >= filtered_list.size() - 1)
        current_dog_position = 0;
    else
        current_dog_position++;
    return filtered_list[current_dog_position];
}

void Service::addToAdoptionList(const Dog& dog) {
    admin_repo->remove(dog);
    user_repo->add(dog);

    auto position = std::find(filtered_list.begin(), filtered_list.end(), dog);
    filtered_list.erase(position);

    std::unique_ptr<Command> currentCommand = std::make_unique<UserCommandAdd>(dog, admin_repo, user_repo);
    user_undo_commands.push(std::move(currentCommand));

    while(!user_redo_commands.empty())
        user_redo_commands.pop();
};

void Service::removeFromAdoptionList(int index) {
    Dog dog = user_repo->getItems()[index];

    admin_repo->add(dog);
    user_repo->remove(dog);

    std::unique_ptr<Command> currentCommand = std::make_unique<UserCommandRemove>(dog, admin_repo, user_repo);
    user_undo_commands.push(std::move(currentCommand));

    while(!user_redo_commands.empty())
        user_redo_commands.pop();
}

void Service::undoUserCommand() {
    if(user_undo_commands.empty())
        throw ServiceException("Cannot undo!");

    std::unique_ptr<Command> command = std::move(user_undo_commands.top());
    user_undo_commands.pop();
    command->undo();
    user_redo_commands.push(std::move(command));
}

void Service::redoUserCommand() {
    if(user_redo_commands.empty())
        throw ServiceException("Cannot redo!");

    std::unique_ptr<Command> command = std::move(user_redo_commands.top());
    user_redo_commands.pop();
    command->redo();
    user_undo_commands.push(std::move(command));
}

const std::vector<Dog>& Service:: getFilteredList() {
    return filtered_list;
}

const std::vector<Dog>& Service::getAdoptedDogs() const {
    return user_repo->getItems();
}

const std::string& Service::getUserRepoFilePath() const {
    return user_repo->getFilePath();
}

bool Service::isNegativeInteger(const std::string& number) {
    if(number.size() < 2 || number[0] != '-' || number[1] == '0')
        return false;

    return std::all_of(number.begin() + 1, number.end(), [] (char c) { return isdigit(c); });
}