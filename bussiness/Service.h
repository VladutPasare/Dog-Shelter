#ifndef KEEP_CALM_AND_ADOPT_A_PET_SERVICE_H
#define KEEP_CALM_AND_ADOPT_A_PET_SERVICE_H
#include "../infrastructure/AdminRepository.h"
#include "../infrastructure/UserHTMLRepository.h"
#include "../validation/DogValidator.h"


class Service {
private:
    AdminRepository<Dog> &admin_repo;
    UserRepository<Dog> *user_repo;
    std::vector <Dog> filtered_list;

    DogValidator dog_validator;
    int current_dog_position = -1;
    int current_dog_position_in_filtered_list = -1;
public:
    explicit Service(AdminRepository<Dog> &admin_repo, UserRepository<Dog> *user_repository) : admin_repo(admin_repo), user_repo(user_repository){}
    void add(const std::string &name, const std::string &breed, const std::string& photo_link, int age);
    void remove(const std::string &name, const std::string &breed);
    void update(const std::string &name, const std::string &breed, const std::string &new_name, const std::string& new_breed, const std::string& new_photo_link, int new_age);
    std::vector <Dog> getDogsFromShelter() const;

    const Dog& nextDog();
    void addToAdoptionList(const Dog& dog);
    void removeFromAdoptionList(const Dog& dog);

    void filter(const std::string& breed, int max_age);
    const Dog& nextDogInFilteredList();
    void addToAdoptionListFromFilteredList(const Dog& dog);

    std::vector<Dog> getAdoptedDogs() const;
    static bool isNegativeInteger(const std::string& number);
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_SERVICE_H
