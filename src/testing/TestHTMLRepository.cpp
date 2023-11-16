#include "TestHTMLRepository.h"
#include <fstream>
#include <cassert>

TestHTMLRepository::TestHTMLRepository() {
    testAdd();
    testRemove();
    testWriteToFile();
}

void TestHTMLRepository::testAdd() {
    HTMLRepository<Dog> html_repository("../files/sample.html");

    Dog dog("Cooper", "Akita", "link", 4);
    html_repository.add(dog);
    assert(html_repository.getItems().size() == 1);
    assert(html_repository.getItems()[0] == dog);
    try{
        html_repository.add(dog);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }
    html_repository.clearFile();
}

void TestHTMLRepository::testRemove() {
    HTMLRepository<Dog> html_repository("../files/sample.html");

    Dog dog("Cooper", "Akita", "link", 4);
    html_repository.add(dog);

    assert(html_repository.getItems()[0] == dog);
    Dog new_dog("Daisy", "Akita", "link", 2);
    try {
        html_repository.remove(new_dog);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }
    assert(html_repository.getItems().size() == 1);
    html_repository.clearFile();
}

void TestHTMLRepository::testWriteToFile() {
    const std::string file_path = "../files/sample.html";
    HTMLRepository<Dog> html_repository(file_path);

    Dog dog("Cooper", "Akita", "link", 4);
    html_repository.add(dog);


    std::string line;
    std::ifstream file(file_path);

    std::getline(file, line);
    assert(line == "<!DOCTYPE html>  ");
    std::getline(file, line);
    assert(line == "<html> ");
    std::getline(file, line);
    assert(line == "<head> ");
    std::getline(file, line);
    assert(line == "    <title>Dog Shelter</title>");
    std::getline(file, line);
    assert(line == "</head> ");
    std::getline(file, line);
    assert(line == "<body> ");
    std::getline(file, line);
    assert(line == "<table border=\"1\"> ");

    std::getline(file, line);
    assert(line == "<tr>         ");
    std::getline(file, line);
    assert(line == "        <td>Name</td>");
    std::getline(file, line);
    assert(line == "           <td>Breed</td>");
    std::getline(file, line);
    assert(line == "        <td>Age</td>");
    std::getline(file, line);
    assert(line == "        <td>Link</td>");
    std::getline(file, line);
    assert(line == "</td>");

    std::getline(file, line);
    assert(line == "<tr>");
    std::getline(file, line);
    assert(line == "        <td>Cooper</td>");
    std::getline(file, line);
    assert(line == "        <td>Akita</td>");
    std::getline(file, line);
    assert(line == "        <td>4</td>");
    std::getline(file, line);
    assert(line == "        <td><a href='link' target='_blank'>link</a></td>");
    std::getline(file, line);
    assert(line == "</tr>");

    std::getline(file, line);
    assert(line == "</tr>");
    std::getline(file, line);
    assert(line == "</table>");
    std::getline(file, line);
    assert(line == "</body>");
    std::getline(file, line);
    assert(line == "</html>");

    html_repository.clearFile();
}
