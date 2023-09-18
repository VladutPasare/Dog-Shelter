#include "MainWindow.h"

MainWindow::MainWindow(Service& service) : service(service) {
    adminWindow = new AdminWindow(service);
    userWindow = new UserWindow(service);

    initWindow();
    connectSignalsAndSlots();
}

void MainWindow::initWindow() {
    this->setFixedSize(460, 400);
    mainLayout = new QVBoxLayout{};
    this->setLayout(mainLayout);
    initButtons();
}

void MainWindow::initButtons() {
    buttonLayout = new QVBoxLayout{};
    mainLayout->addLayout(buttonLayout);

    adminModeButton = new QPushButton{"Admin"};
    adminModeButton->setFixedSize(400, 50);
    buttonLayout->addWidget(adminModeButton, 0, Qt::AlignHCenter);

    userModeButton = new QPushButton{"User"};
    userModeButton->setFixedSize(400, 50);
    buttonLayout->addWidget(userModeButton, 0, Qt::AlignHCenter);

    exitButton = new QPushButton{"Exit"};
    exitButton->setFixedSize(400, 50);
    buttonLayout->addWidget(exitButton, 0, Qt::AlignHCenter);
}

void MainWindow::connectSignalsAndSlots() {
    connect(adminModeButton, &QPushButton::clicked, this, [&] {
        openNewWindow(adminWindow);
    });
    connect(userModeButton, &QPushButton::clicked, this, [&] {
        openNewWindow(userWindow);
    });
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(userWindow, &UserWindow::updateAdminTable, this, [&] () {
        adminWindow->updateTable();
    });
}

