#include "MainWindow.h"

MainWindow::MainWindow(Service& service) : service(service) {
    initWindow();
    connectSignalsAndSlots();
}

void MainWindow::initWindow() {
    //this->setWindowTitle("Select Mode");
    this->resize(400, 400);

    adminWindow = new AdminWindow(service);
    userWindow = new UserWindow(service);

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
    connect(adminModeButton, &QPushButton::clicked, this, &MainWindow::openAdminWindow);
    connect(userModeButton, &QPushButton::clicked, this, &MainWindow::openUserWindow);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(userWindow, &UserWindow::updateAdminTable, this, [&] () {
        adminWindow->updateTable();
    });
}

void MainWindow::openAdminWindow() {
    this->hide();
    adminWindow->show();
    connect(adminWindow, &AdminWindow::back, this, &MainWindow::show);
}

void MainWindow::openUserWindow() {
    this->hide();
    userWindow->show();
    connect(userWindow, &UserWindow::back, this, &MainWindow::show);
}

MainWindow::~MainWindow() {
    delete adminWindow;
    delete userWindow;
    delete mainLayout;
    delete buttonLayout;
    delete adminModeButton;
    delete userModeButton;
    delete exitButton;
}

