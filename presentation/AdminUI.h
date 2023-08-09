#ifndef KEEP_CALM_AND_ADOPT_A_PET_ADMINUI_H
#define KEEP_CALM_AND_ADOPT_A_PET_ADMINUI_H
#include "../bussiness/Service.h"
#include "UI.h"

class AdminUI : public UI{
private:
    const std::string ADD = "1";
    const std::string REMOVE = "2";
    const std::string UPDATE = "3";
    const std::string SEE_DOGS = "4";
    const std::string BACK_TO_MENU = "5";

    Service& service;

public:
    explicit AdminUI(Service& service) : service(service) {}
    void displayMenu() const override;
    void start() override;
    void addDog();
    void removeDog();
    void updateDogInfo();
    void seeDogs();
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_ADMINUI_H
