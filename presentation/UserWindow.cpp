#include "UserWindow.h"
#include <QVBoxLayout>
#include <QLabel>

UserWindow::UserWindow(Service& service, QWidget *parent) : service(service) {
    this->resize(800,650);
    this->setWindowTitle("User");

    newDogsWindow = new NewDogsWindow(service);
    statisticsWindow = new StatisticsWindow(service);

    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->setSpacing(15);
    this->setLayout(mainLayout);

    noDogsMessage = new QMessageBox();
    noDogsMessage->setIcon(QMessageBox::Information);
    noDogsMessage->setText("No dogs!");

    selectDogMessage = new QMessageBox();
    selectDogMessage->setIcon(QMessageBox::Information);
    selectDogMessage->setText("Select a dog!");

    initButtons();
    setUpTable();
    setUpMainMenu();
}

void UserWindow::setUpTable() {
    dogsTable = new CustomTable;
    dogsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dogsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    pictureDelegate = new DogPictureDelegate;

    dogsTable->setItemDelegate(pictureDelegate);
    mainLayout->addWidget(dogsTable);
    dogsTableModel = new DogsTableModel(service.getAdoptedDogs());
    dogsTable->setModel(dogsTableModel);
}

void UserWindow::setUpMainMenu() {
    commandLayout = new QGridLayout;
    mainLayout->addLayout(commandLayout);

    commandLayout->addWidget(newDogsButton, 0, 0);
    commandLayout->addWidget(removeButton, 0, 1);
    commandLayout->addWidget(undoButton, 2, 0);
    commandLayout->addWidget(redoButton, 2, 1);
    commandLayout->addWidget(statisticsButton, 3, 0);
    commandLayout->addWidget(seeExternallyButton, 3, 1);


    mainLayout->addWidget(exitButton);
    mainLayout->setAlignment(exitButton, Qt::AlignCenter);

    connect(newDogsButton, &QPushButton::clicked, this, [&] () {

        service.filter("", -1);

        if(service.getFilteredList().empty())
            noDogsMessage->exec();
        else {
            newDogsWindow->loadNextDogData();
            openNewDogsWindow();
        }
    });

    connect(newDogsWindow, &NewDogsWindow::updateTable, this, [&] () {
        emit dogsTableModel->layoutChanged();
        emit updateAdminTable();
    });

    connect(removeButton, &QPushButton::clicked, this, [&] () {
        QModelIndexList indexes = dogsTable->selectionModel()->selectedIndexes();
        if (indexes.empty()) {
            selectDogMessage->exec();
        }
        else {
            int row = indexes[0].row();
            const Dog& dog = service.getAdoptedDogs()[row];

            try {
                service.removeFromAdoptionList(dog);
                emit updateAdminTable();
            }
            catch (const Exception& e) {

            }
            dogsTableModel->layoutChanged();
            emit updateAdminTable();
        }
        dogsTable->selectionModel()->clear();
    });

    connect(undoButton, &QPushButton::clicked, this, [&] () {
        try {
            service.undoUserCommand();
            dogsTableModel->layoutChanged();
            emit updateAdminTable();
        }
        catch(...) {

        }
    });
    connect(redoButton, &QPushButton::clicked, this, [&] () {
       try {
           service.redoUserCommand();
           dogsTableModel->layoutChanged();
           emit updateAdminTable();
       }
       catch(...) {

       }
    });

    connect(statisticsButton, &QPushButton::clicked, this, [&] () {
        statisticsWindow->populate();
        openStatisticsWindow();
    });

    connect(seeExternallyButton, &QPushButton::clicked, this, [&] () {
        std::string file_path = "../files/file3.html";
        const std::string command = "open " + file_path;
        int exit_code = std::system(command.c_str());
        if(exit_code != 0 ) {
            //std::cout << "An error occurred while opening the file!";
        }
    });

    connect(exitButton, &QPushButton::clicked, this, [&] () {
        this->close();
        back();
    });


}

void UserWindow::openNewDogsWindow() {
    this->hide();
    newDogsWindow->show();
    connect(newDogsWindow, &NewDogsWindow::back, this, &UserWindow::show);
}

void UserWindow::openStatisticsWindow() {
    this->hide();
    statisticsWindow->show();
    connect(statisticsWindow, &StatisticsWindow::back, this, &UserWindow::show);
}

void UserWindow::initButtons() {
    newDogsButton = new CustomButton("New Dogs");
    removeButton = new CustomButton{"Remove"};
    undoButton = new CustomButton("Undo");
    redoButton = new CustomButton("Redo");
    statisticsButton = new CustomButton("Statistics");
    seeExternallyButton = new CustomButton("See externally");
    exitButton = new CustomButton("Exit");
}