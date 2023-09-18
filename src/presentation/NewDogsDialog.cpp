#include "NewDogsDialog.h"

NewDogsDialog::NewDogsDialog(Service &service, QWidget *parent) : service(service), QDialog(parent) {
    this->resize(400, 600);

    mainLayout = new QVBoxLayout{};
    mainLayout->setAlignment(Qt::AlignHCenter);

    filterDialog = new FilterDialog{};

    noDogsMessage = new QMessageBox();
    noDogsMessage->setIcon(QMessageBox::Information);
    noDogsMessage->setText("No dogs!");

    dogDataLayout = new QVBoxLayout{};
    dogPhoto = new QLabel{};
    dogPhoto->setFixedSize(340, 340);

    nameLabel = new QLabel{};
    breedLabel = new QLabel{};
    ageLabel = new QLabel{};

    dogDataLayout->addWidget(dogPhoto);
    dogDataLayout->setSpacing(2);
    dogDataLayout->setAlignment(dogPhoto, Qt::AlignHCenter);
    dogDataLayout->addWidget(nameLabel);
    dogDataLayout->setAlignment(nameLabel, Qt::AlignHCenter);
    dogDataLayout->addWidget(breedLabel);
    dogDataLayout->setAlignment(breedLabel,Qt::AlignHCenter);
    dogDataLayout->addWidget(ageLabel);
    dogDataLayout->setAlignment(ageLabel, Qt::AlignHCenter);

    initButtons();

    buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(adoptButton, 0, 0);
    buttonsLayout->addWidget(skipButton,0, 1);
    buttonsLayout->addWidget(filterButton, 1, 0);
    buttonsLayout->addWidget(returnButton, 1, 1);
    buttonsLayout->setVerticalSpacing(15);
    buttonsLayout->setHorizontalSpacing(35);

    mainLayout->setSpacing(20);
    mainLayout->addItem(dogDataLayout);
    mainLayout->addItem(buttonsLayout);
    this->setLayout(mainLayout);
    mainLayout->setAlignment(dogPhoto, Qt::AlignHCenter);

    connectSignalsAndSlots();
    service.reset_filtered_list();
}

void NewDogsDialog::loadNextDogData() {
    if(!service.getFilteredList().empty()) {
        currentDog = service.nextDog();
        loadImage();
        auto name = QString::fromStdString(currentDog.getName());
        nameLabel->setText(name);
        nameLabel->setAlignment(Qt::AlignCenter);

        nameLabel->setStyleSheet("background-color: white; border: 1px solid rgb(182, 189, 189); border-radius: 1px;");
        nameLabel->setFixedSize(140, 30);

        auto breed = QString::fromStdString("Breed " + currentDog.getBreed());
        breedLabel->setText(breed);
        breedLabel->setAlignment(Qt::AlignCenter);
        breedLabel->setStyleSheet("background-color: white; border: 1px solid rgb(182, 189, 189); border-radius: 1px;");
        breedLabel->setFixedSize(140, 30);

        auto age = QString::fromStdString(std::to_string(currentDog.getAge()));

        if(currentDog.getAge() == 1)
            age += " year old";
        else
            age += " years old";

        ageLabel->setText(age);
        ageLabel->setAlignment(Qt::AlignCenter);
        ageLabel->setStyleSheet("background-color: white; border: 1px solid rgb(182, 189, 189); border-radius: 1px;");
        ageLabel->setFixedSize(140, 30);
    }
}

void NewDogsDialog::loadImage() {
    QPixmap image(QString::fromStdString("../images/" + currentDog.getName() + currentDog.getBreed() + ".png"));

    if(image.isNull()) {
        std::string path = "../images/default.png";
        image = QPixmap(QString::fromStdString(path));
    }

    auto scaledImage = image.scaled(QSize(340, 340));
    dogPhoto->setStyleSheet("border: 1px solid rgb(182, 189, 189);border-radius: 2px");
    dogPhoto->setPixmap(scaledImage);
}

void NewDogsDialog::initButtons() {
    adoptButton = new QPushButton{"Adopt"};
    skipButton = new QPushButton{"Skip"};
    filterButton = new QPushButton{"Filter"};
    returnButton = new QPushButton{"Return"};
}

void NewDogsDialog::connectSignalsAndSlots() {
    connect(adoptButton, &QPushButton::clicked, [&] {
        try {
            service.addToAdoptionList(currentDog);
            emit updateTable();
        }
        catch (...) {

        }

        if(service.getFilteredList().empty()) {
            this->close();
            back();
        }
        else
            loadNextDogData();
    });

    connect(filterButton, &QPushButton::clicked, this, [&] () {
        filterDialog->setBreedComboBoxData(service.getDogBreeds());
        filterDialog->exec();
    });

    connect(filterDialog, &FilterDialog::setFilterData, this, [&] (int maxAge, const std::string& breed) {
        service.filter(breed, maxAge);
        if(service.getFilteredList().empty()) {
            this->close();
            back();
        }
        else
            loadNextDogData();
    });

    connect(skipButton, &QPushButton::clicked, this, [&] {
        loadNextDogData();
    });

    connect(returnButton, &QPushButton::clicked, this, [&] () {
        this->close();
        back();
    });
}