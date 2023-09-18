#include "Command.h"
#include <utility>

Command::Command(std::shared_ptr<FileRepository<Dog>> admin_repository) : admin_repository(std::move(admin_repository)) {}

AdminCommandAdd::AdminCommandAdd(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository) : dog(std::move(dog)), Command(std::move(admin_repository)) {}

void AdminCommandAdd::undo() {
    admin_repository->remove(dog);
}

void AdminCommandAdd::redo() {
    admin_repository->add(dog);
}

AdminCommandRemove::AdminCommandRemove(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository) : dog(std::move(dog)), Command(std::move(admin_repository)) {}

void AdminCommandRemove::undo() {
    admin_repository->add(dog);
}

void AdminCommandRemove::redo() {
    admin_repository->remove(dog);
}

AdminCommandUpdate::AdminCommandUpdate(Dog oldDog, Dog newDog, std::shared_ptr<FileRepository<Dog>> admin_repository) : oldDog(std::move(oldDog)), newDog(std::move(newDog)), Command(std::move(admin_repository)) {}

void AdminCommandUpdate::undo() {
    admin_repository->update(newDog, oldDog);
}

void AdminCommandUpdate::redo() {
    admin_repository->update(oldDog, newDog);
}

UserCommandAdd::UserCommandAdd(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository, std::shared_ptr<Repository<Dog>> user_repository) : dog(std::move(dog)), Command(std::move(admin_repository)), user_repository(std::move(user_repository)) {}

void UserCommandAdd::undo() {
    user_repository->remove(dog);
    admin_repository->add(dog);
}

void UserCommandAdd::redo() {
    user_repository->add(dog);
    admin_repository->remove(dog);
}

UserCommandRemove::UserCommandRemove(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository, std::shared_ptr<Repository<Dog>> user_repository) : dog(std::move(dog)), Command(std::move(admin_repository)), user_repository(std::move(user_repository)) {}

void UserCommandRemove::undo() {
    user_repository->add(dog);
    admin_repository->remove(dog);
}

void UserCommandRemove::redo() {
    user_repository->remove(dog);
    admin_repository->add(dog);
}
