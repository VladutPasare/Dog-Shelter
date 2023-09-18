#include "Dog.h"
#include <sstream>

Dog::Dog(const std::string& name, const std::string& breed, const std::string& link, int age) {
    this->name = name;
    this->breed = breed;
    this->link = link;
    this->age = age;
}

bool operator==(const Dog &d1, const Dog &d2) {
    return d1.name == d2.name && d1.breed == d2.breed;
}

std::istream &operator>>(std::istream &is, Dog &dog) {
    is >> dog.name >> dog.breed >> dog.link >> dog.age;
    return is;
}


std::ostream& operator<<(std::ostream &os, const Dog &dog) {
    os << dog.name << ' ' << dog.breed << ' ' << dog.link << ' ' << dog.age;
    return os;
}

std::string Dog::toString() const {
    std::string DogStr;
    DogStr += "Name: " + name + " | ";
    DogStr += "Breed: " + breed + " | ";
    DogStr += "Link: " + link + " | ";
    DogStr += "Age: " + std::to_string(age);
    return DogStr;
}

std::string Dog::toHTMLFormat() const {
    return "\n<tr>\n"
           "        <td>" + name + "</td>\n"
           "        <td>" + breed + "</td>\n"
           "        <td>" + std::to_string(age) + "</td>\n"
           "        <td><a href='" + link + + "' target='_blank'>" + link + "</a></td>\n"
           "</tr>\n";
}

std::string Dog::toCSVFormat() const {
    return name + ',' + breed + ',' + std::to_string(age) + ',' + link;
}
