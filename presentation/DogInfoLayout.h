#ifndef DOG_SHELTER_DOGINFOLAYOUT_H
#define DOG_SHELTER_DOGINFOLAYOUT_H
#include "../domain/Dog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>

class DogInfoLayout : public QVBoxLayout {
private:
    QLineEdit* nameField;
    QLineEdit* breedField;
    QLineEdit* linkField;
    QComboBox* ageComboBox;

    void setUpWidgets();
public:
    DogInfoLayout();
    explicit DogInfoLayout(const Dog& dog);

    inline std::string getNameFieldText() const { return nameField->text().toStdString(); }
    inline std::string getBreedFieldText() const { return breedField->text().toStdString(); };
    inline std::string getLinkFieldText() const { return linkField->text().toStdString(); }
    inline int getAgeFieldText() const { return ageComboBox->currentText().toInt(); };

    ~DogInfoLayout() override;
};
#endif //DOG_SHELTER_DOGINFOLAYOUT_H
