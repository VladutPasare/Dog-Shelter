#include "AddDogDialog.h"


AddDogDialog::AddDogDialog(Service& service, QWidget *parent) : service(service), QDialog(parent) {

    this->setFixedSize(260, 220);
    mainLayout = new QVBoxLayout{};

    dogInfoLayout = new DogInfoLayout{};

    buttonsLayout = new QHBoxLayout{};

    saveButton = new QPushButton("Save");
    saveButton->setFixedSize(80, 32);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(80, 32);

    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->setAlignment(Qt::AlignHCenter);
    buttonsLayout->setSpacing(8);

    mainLayout->addLayout(dogInfoLayout);
    mainLayout->setAlignment(dogInfoLayout, Qt::AlignHCenter);
    mainLayout->addItem(buttonsLayout);
    this->setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked, this, [=] () {
        std::string name = dogInfoLayout->getNameFieldText();
        std::string breed = dogInfoLayout->getBreedFieldText();
        std::string link = dogInfoLayout->getLinkFieldText();
        int age = dogInfoLayout->getAgeFieldText();
        try {
            this->service.add(name, breed, link, age);
            this->close();
            back();
        }
        catch (const Exception& e) {
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Dog already exists!");
            messageBox.exec();
        }
    });

    connect(cancelButton, &QPushButton::clicked, this, [&] () {
        this->close();
        back();
    });
}
