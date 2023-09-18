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
    assert(dog1.getLink().empty());
    assert(dog1.getAge() == 0);

    // test setters
    dog1.setName("Cooper");
    assert(dog1.getName() == "Cooper");
    dog1.setBreed("Akita");
    assert(dog1.getBreed() == "Akita");
    dog1.setLink("www.google.com");
    assert(dog1.getLink() == "www.google.com");
    dog1.setAge(4);
    assert(dog1.getAge() == 4);

    // test toString
    assert(dog1.toString() == "Name: Cooper | Breed: Akita | Link: www.google.com | Age: 4");

    // test toHTMLFormat
    assert(dog1.toHTMLFormat() == "\n<tr>\n"
                                 "        <td>Cooper</td>\n"
                                 "        <td>Akita</td>\n"
                                 "        <td>4</td>\n"
                                 "        <td><a href='www.google.com' target='_blank'>www.google.com</a></td>\n"
                                 "</tr>\n");

    // test toCSVFormat
    assert(dog1.toCSVFormat() == "Cooper,Akita,4,www.google.com");

    Dog dog2("Cooper", "Akita", "www.google.com", 4);

    // test == operator
    assert(dog1 == dog2);


    std::stringstream ss;

    // test << operator
    ss << dog2;
    assert(ss.str() == "Cooper Akita www.google.com 4");

    // test >> operator
    ss >> dog2;
    assert(dog2.getName() == "Cooper");
    assert(dog2.getBreed() == "Akita");
    assert(dog2.getLink() == "www.google.com");
    assert(dog2.getAge() == 4);
}