#include "UpdateDogDialog.h"

UpdateDogDialog::UpdateDogDialog(Service &service, int index, QWidget *parent) : service(service), index(index), QDialog(parent) {
    this->setFixedSize(320, 500);

    mainLayout = new QVBoxLayout{};
    mainLayout->setAlignment(Qt::AlignHCenter);
    buttonsLayout = new QHBoxLayout{};

    initButtons();
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->setAlignment(Qt::AlignHCenter);
    buttonsLayout->setSpacing(8);

    oldDog = service.getDogsFromShelter()[index];

    QPixmap image(QString::fromStdString("../images/" + oldDog.getName() + oldDog.getBreed() + ".png"));

    if(image.isNull()) {
        std::string path = "../images/default.png";
        image = QPixmap(QString::fromStdString(path));
    }
    auto scaledImage = image.scaled(QSize(220, 220));
    dogPhoto = new QLabel;
    dogPhoto->setFixedSize(220, 220);
    dogPhoto->setPixmap(scaledImage);
    dogInfoLayout = new DogInfoLayout{oldDog};

    mainLayout->addWidget(dogPhoto);
    mainLayout->setAlignment(dogPhoto, Qt::AlignHCenter);
    mainLayout->addItem(dogInfoLayout);
    mainLayout->setAlignment(dogInfoLayout, Qt::AlignHCenter);
    mainLayout->addItem(buttonsLayout);

    this->setLayout(mainLayout);

    connectSignalsAndSlots();
}

void UpdateDogDialog::initButtons() {
    saveButton = new QPushButton("Save");
    saveButton->setFixedSize(100, 32);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(100, 32);
}

void UpdateDogDialog::connectSignalsAndSlots() {
    connect(saveButton, &QPushButton::clicked, this, [=] () {
        std::string new_name = dogInfoLayout->getNameFieldText();
        std::string new_breed = dogInfoLayout->getBreedFieldText();
        std::string new_link = dogInfoLayout->getLinkFieldText();
        int new_age = dogInfoLayout->getAgeFieldText();

        try {
            this->service.update(index, new_name, new_breed, new_link, new_age);

            QDir destinationDirectory("../images");
            QFile file("../images/" + QString::fromStdString(oldDog.getName() + oldDog.getBreed()) + ".png");
            if(file.exists())
                file.rename(destinationDirectory.filePath(QString::fromStdString(new_name + new_breed) + ".png"));
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
