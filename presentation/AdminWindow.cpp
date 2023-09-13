#include "AdminWindow.h"
#include "DogPictureDelegate.h"
#include "../exceptions/ServiceException.h"
#include <QVBoxLayout>
#include <QMessageBox>

AdminWindow::AdminWindow(Service& service, QWidget *parent) : service(service) {
    this->resize(800, 650);
    this->setWindowTitle("Admin");

    mainLayout = new QVBoxLayout;

    selectDogMessage = new QMessageBox();
    selectDogMessage->setIcon(QMessageBox::Information);
    selectDogMessage->setText("Select a dog!");

    this->setLayout(mainLayout);
    initButtons();
    setUpTable();
    setUpMainMenu();
}

void AdminWindow::setUpTable() {
    dogsTable = new CustomTable;
    dogsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dogsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    pictureDelegate = new DogPictureDelegate;

    dogsTable->setItemDelegate(pictureDelegate);
    mainLayout->addWidget(dogsTable);
    dogsTableModel = new DogsTableModel(service.getDogsFromShelter());
    dogsTable->setModel(dogsTableModel);
}

void AdminWindow::setUpMainMenu() {
    commandLayout = new QGridLayout;
    mainLayout->addLayout(commandLayout);

    commandLayout->setSpacing(15);
    commandLayout->addWidget(addButton, 0, 0);
    commandLayout->addWidget(removeButton, 0, 1);
    commandLayout->addWidget(updateButton, 1, 0);
    commandLayout->addWidget(undoButton, 1, 1);
    commandLayout->addWidget(redoButton, 2, 0);
    commandLayout->addWidget(exitButton, 2, 1);


    connect(addButton, &QPushButton::clicked, this, [&] () {
        addDogDialog = new AddDogDialog(service);
        addDogDialog->exec();
        emit dogsTableModel->layoutChanged();
    });

    connect(removeButton, &QPushButton::clicked, this, [&] () {
        QModelIndexList indexes = dogsTable->selectionModel()->selectedIndexes();
        if (indexes.empty()) {
            selectDogMessage->exec();
        }
        else {
            std::string name = service.getDogsFromShelter()[indexes[0].row()].getName();
            std::string breed = service.getDogsFromShelter()[indexes[0].row()].getBreed();
            service.remove(indexes[0].row());
            emit dogsTableModel->layoutChanged();
            dogsTable->selectionModel()->clear();
        }
    });

    connect(updateButton, &QPushButton::clicked, this, [&]() {

        QModelIndexList indexes = dogsTable->selectionModel()->selectedIndexes();

        if (indexes.empty()) {
            selectDogMessage->exec();
        }
        else {
            updateDogDialog = new UpdateDogDialog(service, indexes[0].row());
            updateDogDialog->exec();
            emit dogsTableModel->layoutChanged();
            dogsTable->selectionModel()->clear();
        }
    });

    connect(undoButton, &QPushButton::clicked, this, [&]() {
        try {
            service.undoAdminCommand();
            emit dogsTableModel->layoutChanged();
        }
        catch (const ServiceException& e) {

        }
    });

    connect(redoButton, &QPushButton::clicked, this, [&]() {
        try {
            service.redoAdminCommand();
            emit dogsTableModel->layoutChanged();
        }
        catch (const ServiceException& e) {

        }
    });

    connect(exitButton, &QPushButton::clicked, this, [&]() {
        this->close();
        back();
    });

}

AdminWindow::~AdminWindow() {
    delete updateDogDialog;
    delete addDogDialog;
    delete pictureDelegate;
    delete mainLayout;
    delete dogsTable;
    delete dogsTableModel;
    delete commandLayout;
    delete addButton;
    delete removeButton;
    delete updateButton;
    delete undoButton;
    delete redoButton;
    delete exitButton;
    delete selectDogMessage;
}

void AdminWindow::updateTable() {
    dogsTableModel->layoutChanged();
}

void AdminWindow::initButtons() {
    addButton = new CustomButton("Add");
    removeButton = new CustomButton("Remove");
    updateButton = new CustomButton("Update");
    undoButton = new CustomButton("Undo");
    redoButton = new CustomButton("Redo");
    exitButton = new CustomButton("Exit");
}