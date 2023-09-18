#ifndef DOG_SHELTER_MAINWINDOW_H
#define DOG_SHELTER_MAINWINDOW_H
#include "Window.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "UserWindow.h"
#include "AdminWindow.h"


class MainWindow : public Window {
private:
    Service& service;
    AdminWindow *adminWindow;
    UserWindow *userWindow;
    QVBoxLayout *mainLayout;
    QVBoxLayout *buttonLayout;
    QPushButton *adminModeButton;
    QPushButton *userModeButton;
    QPushButton *exitButton;

    void initWindow();
    void initButtons();
    void connectSignalsAndSlots();
public:
    explicit MainWindow(Service& service);
};


#endif //DOG_SHELTER_MAINWINDOW_H
