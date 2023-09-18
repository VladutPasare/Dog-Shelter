#include "AddDogDialog.h"

AddDogDialog::AddDogDialog(Service& service, QWidget *parent) : service(service), QDialog(parent) {

    this->setFixedSize(320, 500);
    mainLayout = new QVBoxLayout{};

    imageDrop = new ImageDrop{};
    dogInfoLayout = new DogInfoLayout{};
    buttonsLayout = new QHBoxLayout{};

    initButtons();

    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->setAlignment(Qt::AlignHCenter);
    buttonsLayout->setSpacing(8);

    mainLayout->addWidget(imageDrop);
    mainLayout->setAlignment(imageDrop, Qt::AlignHCenter);
    mainLayout->addLayout(dogInfoLayout);
    mainLayout->setAlignment(dogInfoLayout, Qt::AlignHCenter);
    mainLayout->addItem(buttonsLayout);
    this->setLayout(mainLayout);

    connectSignalsAndSlots();
}

void AddDogDialog::initButtons() {
    saveButton = new QPushButton("Save");
    saveButton->setFixedSize(80, 32);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(80, 32);
}

void AddDogDialog::connectSignalsAndSlots() {
    connect(saveButton, &QPushButton::clicked, this, [=] () {
        std::string name = dogInfoLayout->getNameFieldText();
        std::string breed = dogInfoLayout->getBreedFieldText();
        std::string link = dogInfoLayout->getLinkFieldText();
        int age = dogInfoLayout->getAgeFieldText();
        try {
            this->service.add(name, breed, link, age);
            imageDrop->save(QString::fromStdString(name + breed) + ".png");
            this->close();
            back();
        }
        catch (const Exception& e) {
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText(QString::fromStdString(e.getErrorMessage()));
            messageBox.exec();
        }
    });

    connect(cancelButton, &QPushButton::clicked, this, [&] () {
        this->close();
        back();
    });
}
