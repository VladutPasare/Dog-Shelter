#include "TestFileRepository.h"
#include <fstream>

TestFileRepository::TestFileRepository() {
    testAdd();
    testRemove();
    testUpdate();
    testWriteToFile();
    testReadFromFile();
}

void TestFileRepository::testAdd() {
    FileRepository<Dog> file_repository("../files/sample.txt");

    Dog d1("Cooper", "Akita", "link", 4);
    file_repository.add(d1);
    assert(file_repository.getItems().size() == 1);
    assert(file_repository.getItems()[0] == d1);
    assert(file_repository.getIndex(d1) == 0);

    Dog d2("Cooper", "Akita", "link", 4);

    try {
        file_repository.add(d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The provided item already exists in the repository!");
    }

    d2.setName("Daisy");
    file_repository.add(d2);
    assert(file_repository.getItems().size() == 2);
    assert(file_repository.getItems()[1] == d2);
    assert(file_repository.getIndex(d2) == 1);

    file_repository.clearFile();
}

void TestFileRepository::testRemove() {
    FileRepository<Dog> file_repository("../files/sample.txt");

    Dog d1("Cooper", "Akita", "link", 4);
    Dog d2("Daisy", "Akita", "Photo linkField", 4);

    file_repository.add(d1);
    file_repository.add(d2);
    assert(file_repository.getItems().size() == 2);

    file_repository.remove(d1);

    try {
        file_repository.remove(d1);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    assert(file_repository[0] == d2);
    file_repository.remove(d2);

    try {
        file_repository.remove(d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    file_repository.clearFile();
}

void TestFileRepository::testUpdate() {
    FileRepository<Dog> file_repository("../files/sample.txt");
    file_repository.clearFile();

    Dog d1("Cooper", "Akita", "link", 4);
    Dog d2("Charlie", "Akita", "link", 5);
    Dog d3("Charlie", "Akita", "link", 7);
    try {
        file_repository.update(d1, d2);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "Provided item not in repository!");
    }

    file_repository.add(d1);
    file_repository.add(d2);
    try {
        file_repository.update(d1, d3);
        assert(false);
    }
    catch(const RepositoryException& e) {
        assert(e.getErrorMessage() == "The new item already exists in the repository!");
    }

    d3.setName("Daisy");
    file_repository.update(d1, d3);
    assert(file_repository[1].getName() == "Daisy");
    assert(file_repository.getItems().size() == 2);

    file_repository.clearFile();
}

void TestFileRepository::testReadFromFile() {
    const std::string file_path = "../files/sample.txt";
    std::ofstream file(file_path);

    file << "Cooper Akita link 4\n";
    file << "Daisy Akita  link 2";

    file.close();

    // read function automatically called by the constructor
    FileRepository<Dog> file_repository(file_path);

    assert(file_repository.getItems().size() == 2);
    assert(file_repository.getItems()[0] == Dog("Cooper", "Akita", "link", 4));
    assert(file_repository.getItems()[1] == Dog("Daisy", "Akita", "link", 2));

    file_repository.clearFile();
}

void TestFileRepository::testWriteToFile() {
    const std::string file_path = "../files/sample.txt";
    FileRepository<Dog> file_repository(file_path);

    file_repository.add(Dog("Daisy", "Akita", "link", 1));
    file_repository.add(Dog("Charlie", "Akita", "link", 3));

    std::ifstream file(file_path);
    Dog dog;

    file >> dog;
    assert(dog == Dog("Daisy", "Akita", "link", 1));

    file >> dog;
    assert(dog == Dog("Charlie", "Akita", "link", 3));

    file.close();
    file_repository.clearFile();
}
