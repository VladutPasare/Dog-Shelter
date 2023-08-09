#include "MainUI.h"
#include <iostream>

std::string MainUI::getOption() {
    displayMenu();
    std::string option;
    std::getline(std::cin, option);

    if(option != "1" && option != "2" && option!= "3")
        std::cout << "\nInvalid command!";

    return option;
}

void MainUI::displayMenu(){
    std::cout << "\n1. Administrator\n";
    std::cout << "2. User\n";
    std::cout << "3. Exit\n";
    std::cout << "\n>> ";
}