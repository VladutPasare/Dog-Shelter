#ifndef KEEP_CALM_AND_ADOPT_A_PET_DOG_H
#define KEEP_CALM_AND_ADOPT_A_PET_DOG_H
#include <string>


class Dog {
private:
    std::string name, breed, photo_link;
    int age;
public:
    explicit Dog(const std::string &name = "", const std::string &breed = "", const std::string &photo_link = "", int age = 0);
    inline std::string getName() const { return name; }
    inline std::string getBreed() const { return breed; }
    inline std::string getPhotoLink() const { return photo_link; }
    inline int getAge() const { return age; }

    inline void setName(const std::string &new_name) { this->name = new_name; }
    inline void setBreed(const std::string& new_breed) { this->breed = new_breed; }
    inline void setPhotoLink(const std::string &new_photo_link) { this->photo_link = new_photo_link; }
    inline void setAge(int new_age) { this->age = new_age; }

    std::string toString() const;
    std::string toHTMLFormat() const;

    friend bool operator==(const Dog& d1, const Dog& d2);
    friend std::istream& operator>>(std::istream& is, Dog& dog);
    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};

#endif //KEEP_CALM_AND_ADOPT_A_PET_DOG_H
