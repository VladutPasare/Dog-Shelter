#include "UserWindow.h"
#include <QVBoxLayout>
#include <QLabel>

UserWindow::UserWindow(Service& service, QWidget *parent) : service(service) {
    this->resize(800,650);
    this->setWindowTitle("User");

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
    connectSignalsAndSlots();
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

void UserWindow::connectSignalsAndSlots() {
    connect(newDogsButton, &QPushButton::clicked, this, [&] () {
        service.reset_filtered_list();

        if(service.getFilteredList().empty())
            noDogsMessage->exec();
        else {
            newDogsDialog = new NewDogsDialog(service);
            newDogsDialog->loadNextDogData();
            connect(newDogsDialog, &NewDogsDialog::updateTable, this, [&] () {
                emit dogsTableModel->layoutChanged();
                emit updateAdminTable();
            });
            newDogsDialog->exec();
            emit dogsTableModel->layoutChanged();
            emit updateAdminTable();
            delete newDogsDialog;
        }
    });

    connect(removeButton, &QPushButton::clicked, this, [&] () {
        QModelIndexList indexes = dogsTable->selectionModel()->selectedIndexes();
        if (indexes.empty()) {
            selectDogMessage->exec();
        }
        else {

            try {
                service.removeFromAdoptionList(indexes[0].row());
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
        catch(Exception& e) {
            //std::cout<<e.getErrorMessage();
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
        openNewWindow(statisticsWindow);
    });

    connect(seeExternallyButton, &QPushButton::clicked, this, [&] () {
        const std::string command = "open " + service.getUserRepoFilePath();
        int exit_code = std::system(command.c_str());
        if(exit_code != 0) {
            // error
        }
    });

    connect(exitButton, &QPushButton::clicked, this, [&] () {
        this->close();
        back();
    });
}
