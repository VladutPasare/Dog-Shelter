#include "UpdateDogDialog.h"

UpdateDogDialog::UpdateDogDialog(Service &service, int index, QWidget *parent) : service(service), QDialog(parent) {
    this->setFixedSize(360, 440);

    mainLayout = new QVBoxLayout{};
    mainLayout->setAlignment(Qt::AlignHCenter);
    buttonsLayout = new QHBoxLayout{};

    saveButton = new QPushButton("Save");
    saveButton->setFixedSize(100, 32);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(100, 32);

    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->setAlignment(Qt::AlignHCenter);
    buttonsLayout->setSpacing(8);

    const Dog& oldDog = service.getDogsFromShelter()[index];
    std::string name = oldDog.getName();
    std::string breed = oldDog.getBreed();

    QPixmap image(QString::fromStdString("../images/" + name + breed + ".png"));

    if(image.isNull()) {
        std::string path = "../images/default.png";
        image = QPixmap(QString::fromStdString(path));
    }
    auto scaledImage = image.scaled(QSize(220, 220));
    auto* dogPhoto = new QLabel;

    dogPhoto->setPixmap(scaledImage);
    dogPhoto->setStyleSheet("border: 1px solid rgb(182, 189, 189); border-radius: 2px");
    auto dogInfoLayout = new DogInfoLayout{oldDog};

    mainLayout->addWidget(dogPhoto);
    mainLayout->setAlignment(dogPhoto, Qt::AlignHCenter);
    mainLayout->addItem(dogInfoLayout);
    mainLayout->setAlignment(dogInfoLayout, Qt::AlignHCenter);
    mainLayout->addItem(buttonsLayout);

    this->setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked, this, [=] () {
        std::string new_name = dogInfoLayout->getNameFieldText();
        std::string new_breed = dogInfoLayout->getBreedFieldText();
        std::string new_link = dogInfoLayout->getLinkFieldText();
        int new_age = dogInfoLayout->getAgeFieldText();

        try {
            this->service.update(index, new_name, new_breed, new_link, new_age);
            this->close();
            back();
        }
        catch (const Exception& e) {
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setWindowTitle("Error!");
            messageBox.setText(QString::fromStdString(e.getErrorMessage()));
            messageBox.exec();
        }
    });

    connect(cancelButton, &QPushButton::clicked, this, [&] () {
        this->close();
        back();
    });
}
