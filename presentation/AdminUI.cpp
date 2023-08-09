#include "AdminUI.h"
#include <iostream>
using namespace std;

void AdminUI::addDog(){
    string name, breed, photo_link, age_string;

    cout << "\nName: ";
    getline(cin, name);
    cout << "Breed: ";
    getline(cin, breed);
    cout << "Photo link: ";
    getline(cin, photo_link);
    cout << "Age: ";
    getline(cin, age_string);

    if(Service::isNegativeInteger(age_string))
        throw UIException( "Age must be a positive number!");

    try{
        service.add(name, breed, photo_link, stoi(age_string));
    }
    catch(ServiceException& exception){
        cout << '\n' << exception.getErrorMessage() << '\n';
        return;
    }

    cout << "\nDog successfully added!\n";
}

void AdminUI::removeDog(){
    string name, breed;
    cout << "\nName: ";
    getline(cin, name);
    cout << "Breed: ";
    getline(cin, breed);
    try{
        service.remove(name, breed);
    }
    catch(ServiceException& exception){
        cout << '\n' << exception.getErrorMessage() << '\n';
        return;
    }
    cout << "\nDog successfully removed!\n";
}

void AdminUI::updateDogInfo(){
    string name, breed, new_name, new_breed, new_photo_link, new_age_string;

    cout << "\nName: ";
    getline(cin, name);
    cout << "Breed: ";
    getline(cin, breed);
    cout << "\nNew name: ";
    getline(cin, new_name);
    cout << "New breed: ";
    getline(cin, new_breed);
    cout << "New photo link: ";
    getline(cin, new_photo_link);
    cout << "New age: ";
    getline(cin, new_age_string);

    if(Service::isNegativeInteger(new_age_string))
        throw UIException("New age must a positive number!");

    try{
        service.update(name, breed, new_name, new_breed, new_photo_link, stoi(new_age_string));
    }
    catch(ServiceException& exception){
        cout << '\n' << exception.getErrorMessage() << '\n';
        return;
    }

    cout << "\nDog Info successfully updated!\n";
}

void AdminUI::seeDogs() {
    vector <Dog> dogs = service.getDogsFromShelter();

    for(const Dog& dog : dogs)
        cout << dog.toString() << '\n';
}

void AdminUI::start() {
    string user_command;

    while(true) {
        displayMenu();
        user_command = UI::getUserCommand();

        try {
            if (user_command == ADD) {
                addDog();
            } else if (user_command == REMOVE) {
                removeDog();
            } else if (user_command == UPDATE) {
                updateDogInfo();
            } else if(user_command == SEE_DOGS){
                seeDogs();
            } else if (user_command == BACK_TO_MENU) {
                break;
            } else
                cout << "\nInvalid command!\n";
        }
        catch (const UIException& exception){
            cout << '\n' << exception.getErrorMessage() << '\n';
        }
    }
}

void AdminUI::displayMenu() const{
    cout << "\n1. Add dog\n"
            "2. Remove dog\n"
            "3. Update dog info\n"
            "4. See dogs\n"
            "5. Exit\n";
}

