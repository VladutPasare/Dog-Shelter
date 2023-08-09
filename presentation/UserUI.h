#ifndef KEEP_CALM_AND_ADOPT_A_PET_USERUI_H
#define KEEP_CALM_AND_ADOPT_A_PET_USERUI_H
#include "UI.h"

class UserUI : public UI{
private:
    const std::string SEE_DOGS_ONE_BY_ONE = "1";
    const std::string ADOPT_DOG = "1";
    const std::string SKIP = "2";
    const std::string BACK_TO_MENU = "3";
    const std::string FILTER = "2";
    const std::string SEE_ADOPTION_LIST = "3";
    const std::string BACK = "4";

    Service& service;
    std::string file_path;

public:
    explicit UserUI(Service& service, std::string& file_path) : service(service), file_path(file_path) {}
    void displayMenu() const override;
    void start() override;
    void see_dogs_one_by_one();
    void filter();
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_USERUI_H
