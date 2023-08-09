#include "UI.h"
#include <iostream>
using namespace std;


std::string UI::getUserCommand() {
    std::string userCommand;
    cout << "\n>> ";
    getline(std::cin, userCommand);
    return userCommand;
}

