#ifndef DOG_SHELTER_COMMAND_H
#define DOG_SHELTER_COMMAND_H
#include "../domain/Dog.h"
#include "../infrastructure/Repository.h"

class Command {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~Command() = default;
};

class AdminCommandAdd : public Command {
private:
    Dog dog;
    std::shared_ptr<Repository<Dog>> repository;
public:
    AdminCommandAdd(Dog dog, std::shared_ptr<Repository<Dog>> repository);
    void undo() override;
    void redo() override;
};

class AdminCommandRemove : public Command {
    Dog dog;
    std::shared_ptr<Repository<Dog>> repository;
public:
    AdminCommandRemove(Dog dog, std::shared_ptr<Repository<Dog>> repository);
    void undo() override;
    void redo() override;
};

class AdminCommandUpdate : public Command {
    Dog oldDog;
    Dog newDog;
    std::shared_ptr<Repository<Dog>> repository;
public:
    AdminCommandUpdate(Dog oldDog, Dog newDog, std::shared_ptr<Repository<Dog>> repository);
    void undo() override;
    void redo() override;
};

class UserCommandAdd : public Command {
    Dog dog;
    std::shared_ptr<Repository<Dog>> adminRepository;
    std::shared_ptr<Repository<Dog>> userRepository;
public:
    UserCommandAdd(Dog dog, std::shared_ptr<Repository<Dog>> adminRepository, std::shared_ptr<Repository<Dog>> userRepository);
    void undo() override;
    void redo() override;
};

class UserCommandRemove : public Command {
    Dog dog;
    std::shared_ptr<Repository<Dog>> adminRepository;
    std::shared_ptr<Repository<Dog>> userRepository;
public:
    UserCommandRemove(Dog dog, std::shared_ptr<Repository<Dog>> adminRepository, std::shared_ptr<Repository<Dog>> userRepository);
    void undo() override;
    void redo() override;
};
#endif //DOG_SHELTER_COMMAND_H
