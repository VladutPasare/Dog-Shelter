#include "Command.h"

#include <utility>

AdminCommandAdd::AdminCommandAdd(Dog dog, std::shared_ptr<Repository<Dog>> repository) : dog(std::move(dog)), repository(std::move(repository)) {}

void AdminCommandAdd::undo() {
    repository->remove(dog);
}

void AdminCommandAdd::redo() {
    repository->add(dog);
}

AdminCommandRemove::AdminCommandRemove(Dog dog, std::shared_ptr<Repository<Dog>> repository) : dog(std::move(dog)), repository(std::move(repository)) {}

void AdminCommandRemove::undo() {
    repository->add(dog);
}

void AdminCommandRemove::redo() {
    repository->remove(dog);
}

AdminCommandUpdate::AdminCommandUpdate(Dog oldDog, Dog newDog, std::shared_ptr<Repository<Dog>> repository) : oldDog(std::move(oldDog)), newDog(std::move(newDog)), repository(std::move(repository)) {

}

void AdminCommandUpdate::undo() {
    repository->update(newDog, oldDog);
}

void AdminCommandUpdate::redo() {
    repository->update(oldDog, newDog);
}

UserCommandAdd::UserCommandAdd(Dog dog, std::shared_ptr<Repository<Dog>> adminRepository,
                               std::shared_ptr<Repository<Dog>> userRepository) : dog(std::move(dog)), adminRepository(std::move(adminRepository)), userRepository(std::move(userRepository)) {}

void UserCommandAdd::undo() {
    userRepository->remove(dog);
    adminRepository->add(dog);
}

void UserCommandAdd::redo() {
    userRepository->add(dog);
    adminRepository->remove(dog);
}

UserCommandRemove::UserCommandRemove(Dog dog, std::shared_ptr<Repository<Dog>> adminRepository,
                                     std::shared_ptr<Repository<Dog>> userRepository) : dog(std::move(dog)), adminRepository(std::move(adminRepository)), userRepository(std::move(userRepository)) {}

void UserCommandRemove::undo() {
    userRepository->add(dog);
    adminRepository->remove(dog);
}

void UserCommandRemove::redo() {
    userRepository->remove(dog);
    adminRepository->add(dog);
}
