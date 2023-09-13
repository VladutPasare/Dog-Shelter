#ifndef DOG_SHELTER_MAINWINDOW_H
#define DOG_SHELTER_MAINWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "UserWindow.h"
#include "AdminWindow.h"


class MainWindow : public QWidget {
    Q_OBJECT
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
    void openAdminWindow();
    void openUserWindow();
public:
    explicit MainWindow(Service& service);
    ~MainWindow() override;
};


#endif //DOG_SHELTER_MAINWINDOW_H
