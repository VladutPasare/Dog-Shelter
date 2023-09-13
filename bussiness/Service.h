#ifndef DOG_SHELTER_SERVICE_H
#define DOG_SHELTER_SERVICE_H
#include "../infrastructure/FileRepository.h"
#include "../infrastructure/HTMLRepository.h"
#include "../validation/DogValidator.h"
#include "Command.h"
#include <stack>
#include <set>
#include <memory>

class Service {
private:
    std::shared_ptr<FileRepository<Dog>> admin_repo;
    std::shared_ptr<Repository<Dog>> user_repo;
    std::vector <Dog> filtered_list;
    DogValidator dog_validator;
    int current_dog_position = -1;

    std::stack<std::unique_ptr<Command>> admin_undo_commands;
    std::stack<std::unique_ptr<Command>> admin_redo_commands;
    std::stack<std::unique_ptr<Command>> user_undo_commands;
    std::stack<std::unique_ptr<Command>> user_redo_commands;

public:
    explicit Service(std::shared_ptr<FileRepository<Dog>> admin_repo, std::shared_ptr<Repository<Dog>> user_repository);
    void add(const std::string &name, const std::string &breed, const std::string& photo_link, int age);
    void remove(int index);
    void update(int index, const std::string &new_name, const std::string& new_breed, const std::string& new_photo_link, int new_age);
    const std::vector<Dog>& getDogsFromShelter() const;
    std::set<std::string> getDogBreeds();
    unsigned int countDogsByBreed(const std::string& breed) const;
    void undoAdminCommand();
    void redoAdminCommand();

    void filter(const std::string& breed, int max_age);
    const Dog& nextDog();
    void addToAdoptionList(const Dog& dog);
    void removeFromAdoptionList(const Dog& dog);
    const std::vector<Dog>& getFilteredList();
    void undoUserCommand();
    void redoUserCommand();

    const std::vector<Dog>& getAdoptedDogs() const;
    static bool isNegativeInteger(const std::string& number);
};

#endif //DOG_SHELTER_SERVICE_H
