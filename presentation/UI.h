#ifndef KEEP_CALM_AND_ADOPT_A_PET_UI_H
#define KEEP_CALM_AND_ADOPT_A_PET_UI_H
#include "../bussiness/Service.h"
#include "../exceptions/ServiceException.h"
#include "../exceptions/UIException.h"

class UI{
private:
    const std::string ADMINISTRATOR_MODE = "1";
    const std::string USER_MODE = "2";
    const std::string EXIT = "3";

public:
    virtual void start() = 0;
    virtual void displayMenu() const = 0;
    static std::string getUserCommand();
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_UI_H
