#include "UserUI.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void UserUI::displayMenu() const {
    cout << "\n1. See admin_repo one by one\n";
    cout << "2. Filter\n";
    cout << "3. See adoption list\n";
    cout << "4. Back\n";
}

void UserUI::see_dogs_one_by_one() {
    try {
        while (true) {
            std::string option;
            const Dog& currentDog = service.nextDog();
            cout << '\n' <<  currentDog.toString() << '\n';
            cout << "\n1. Adopt\n"
                    "2. Skip\n"
                    "3. Back to menu\n";
            cout << "\n>> ";
            getline(cin, option);

            if (option == ADOPT_DOG) {
                service.addToAdoptionList(currentDog);
            } else if (option == SKIP) {

            } else if (option == BACK_TO_MENU) {
                break;
            } else
                cout << "\nInvalid option!\n";
        }
    }
    catch (const ServiceException& exception) {
        throw UIException(exception.getErrorMessage());
    }
}

void UserUI::filter() {
    std::string breed, age;
    cout << "\nBreed: ";
    getline(cin, breed);
    cout << "Maximum age: ";
    getline(cin, age);

    if(Service::isNegativeInteger(age))
        throw UIException("Age must be a positive number!");

    service.filter(breed, stoi(age));

    while(true) {
        std::string option;
        try {
            const Dog& dog = service.nextDogInFilteredList();
            cout << '\n' <<  dog.toString() << '\n';
            cout << "\n1. Adopt\n"
                    "2. Skip\n"
                    "3. Back to menu\n";
            cout << "\n>> ";
            getline(cin, option);

            if (option == ADOPT_DOG) {
                service.addToAdoptionListFromFilteredList(dog);
            } else if (option == SKIP) {

            } else if (option == BACK_TO_MENU) {
                break;
            } else
                cout << "\nInvalid option!\n";
        }
        catch (const ServiceException &exception) {
            throw UIException(exception.getErrorMessage());
        }
    }
}

void UserUI::start() {
    std::string user_command;

    while(true) {
        try {
            displayMenu();
            user_command = UI::getUserCommand();

            if (user_command == SEE_DOGS_ONE_BY_ONE) {
                see_dogs_one_by_one();
            } else if (user_command == FILTER) {
                filter();
            } else if (user_command == SEE_ADOPTION_LIST) {

                std::vector<Dog> dogs = service.getAdoptedDogs();
                if(dogs.empty()) {
                    std::cout << "\nNo adopted dogs!\n";
                }
                else {
                    const std::string command = "open " + std::string(file_path);
                    int exit_code = std::system(command.c_str());
                    if (exit_code != 0) {
                        std::cout << "\nCould not open the filePath!\n";
                    }
                }
            } else if (user_command == BACK) {
                break;
            } else
                cout << "\nInvalid command!\n";
        }
        catch (const UIException& exception) {
            cout << '\n' << exception.getErrorMessage() << '\n';
        }
    }
}
