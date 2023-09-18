#ifndef DOG_SHELTER_DOG_H
#define DOG_SHELTER_DOG_H
#include <string>

class Dog {
private:
    std::string name, breed, link;
    int age;
public:
    explicit Dog(const std::string &name = "", const std::string &breed = "", const std::string &link = "", int age = 0);
    inline const std::string& getName() const { return name; }
    inline const std::string& getBreed() const { return breed; }
    inline const std::string& getLink() const { return link; }
    inline const int getAge() const { return age; }

    inline void setName(const std::string &new_name) { this->name = new_name; }
    inline void setBreed(const std::string& new_breed) { this->breed = new_breed; }
    inline void setLink(const std::string &new_link) { this->link = new_link; }
    inline void setAge(int new_age) { this->age = new_age; }

    std::string toString() const;
    std::string toHTMLFormat() const;
    std::string toCSVFormat() const;

    friend bool operator==(const Dog& d1, const Dog& d2);
    friend std::istream& operator>>(std::istream& is, Dog& dog);
    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};

#endif //DOG_SHELTER_DOG_H
