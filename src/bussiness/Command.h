#ifndef DOG_SHELTER_COMMAND_H
#define DOG_SHELTER_COMMAND_H
#include "../domain/Dog.h"
#include "../infrastructure/FileRepository.h"
#include "../infrastructure/Repository.h"

class Command {
protected:
    std::shared_ptr<FileRepository<Dog>> admin_repository;
public:
    explicit Command(std::shared_ptr<FileRepository<Dog>> admin_repository);
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~Command() = default;
};

class AdminCommandAdd : public Command {
private:
    Dog dog;
public:
    AdminCommandAdd(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository);
    void undo() override;
    void redo() override;
};

class AdminCommandRemove : public Command {
private:
    Dog dog;
public:
    AdminCommandRemove(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository);
    void undo() override;
    void redo() override;
};

class AdminCommandUpdate : public Command {
private:
    Dog oldDog;
    Dog newDog;
public:
    AdminCommandUpdate(Dog oldDog, Dog newDog, std::shared_ptr<FileRepository<Dog>> admin_repository);
    void undo() override;
    void redo() override;
};

class UserCommandAdd : public Command {
private:
    Dog dog;
    std::shared_ptr<Repository<Dog>> user_repository;
public:
    UserCommandAdd(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository, std::shared_ptr<Repository<Dog>> user_repository);
    void undo() override;
    void redo() override;
};

class UserCommandRemove : public Command {
private:
    Dog dog;
    std::shared_ptr<Repository<Dog>> user_repository;
public:
    UserCommandRemove(Dog dog, std::shared_ptr<FileRepository<Dog>> admin_repository, std::shared_ptr<Repository<Dog>> user_repository);
    void undo() override;
    void redo() override;
};

#endif //DOG_SHELTER_COMMAND_H
