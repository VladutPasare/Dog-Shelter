#include "DogInfoLayout.h"

DogInfoLayout::DogInfoLayout() {
    setUpWidgets();
}

DogInfoLayout::DogInfoLayout(const Dog &dog) {
    setUpWidgets();
    nameField->setText(QString::fromStdString(dog.getName()));
    breedField->setText(QString::fromStdString(dog.getBreed()));
    linkField->setText(QString::fromStdString(dog.getLink()));
    ageComboBox->setCurrentText(QString::number(dog.getAge()));
}

void DogInfoLayout::setUpWidgets() {

    nameField = new QLineEdit();
    nameField->setPlaceholderText("Name");
    nameField->setStyleSheet("padding: 2px;");
    nameField->setFixedSize(140, 24);

    breedField = new QLineEdit();
    breedField->setPlaceholderText("Breed");
    breedField->setStyleSheet("padding: 2px;");
    breedField->setFixedSize(140, 24);

    linkField = new QLineEdit();
    linkField->setPlaceholderText("Link");
    linkField->setStyleSheet("padding: 2px;");
    linkField->setFixedSize(140, 24);

    ageComboBox = new QComboBox();
    ageComboBox->setPlaceholderText("Age");

    for(int i = 1; i <= 35; i++)
        ageComboBox->addItem(QString::number(i));

    this->addWidget(nameField);
    this->addWidget(breedField);
    this->addWidget(linkField);
    this->addWidget(ageComboBox);


    ageComboBox->setFixedSize(80, 30);

    this->setSpacing(8);
}
