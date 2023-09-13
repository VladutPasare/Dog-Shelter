#include "TestDomain.h"
#include "../domain/Dog.h"
#include <cassert>
#include <sstream>

TestDomain::TestDomain() {
    testDog();
}

void TestDomain::testDog() {
    Dog dog1;

    // test default constructor
    assert(dog1.getName().empty());
    assert(dog1.getBreed().empty());
    assert(dog1.getPhotoLink().empty());
    assert(dog1.getAge() == 0);

    // test setters
    dog1.setName("Cooper");
    assert(dog1.getName() == "Cooper");
    dog1.setBreed("Akita");
    assert(dog1.getBreed() == "Akita");
    dog1.setPhotoLink("null");
    assert(dog1.getPhotoLink() == "null");
    dog1.setAge(4);
    assert(dog1.getAge() == 4);

    // test toString
    assert(dog1.toString() == "Name: Cooper | Breed: Akita | Photo linkField: null | Age: 4");

    // test toHTMLFormat
    assert(dog1.toHTMLFormat() == "\n<tr>\n"
                                 "        <td>Cooper</td>\n"
                                 "        <td>Akita</td>\n"
                                 "        <td>null</td>\n"
                                 "        <td>4</td>\n"
                                 "</tr>");


    Dog dog2("Cooper", "Akita", "null", 4);

    // test == operator
    assert(dog1 == dog2);


    std::stringstream ss;

    // test << operator
    ss << dog2;
    assert(ss.str() == "Cooper Akita null 4");

    // test >> operator
    ss >> dog2;
    assert(dog2.getName() == "Cooper");
    assert(dog2.getBreed() == "Akita");
    assert(dog2.getPhotoLink() == "null");
    assert(dog2.getAge() == 4);
}