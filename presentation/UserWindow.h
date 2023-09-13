#ifndef DOG_SHELTER_USERWINDOW_H
#define DOG_SHELTER_USERWINDOW_H
#include "NewDogsWindow.h"
#include "../bussiness/Service.h"
#include "CustomTable.h"
#include "CustomButton.h"
#include "DogsTableModel.h"
#include "DogPictureDelegate.h"
#include "StatisticsWindow.h"
#include <QWidget>
#include <QPushButton>

class UserWindow : public QWidget {
    Q_OBJECT
private:
    Service& service;

    NewDogsWindow* newDogsWindow;
    StatisticsWindow* statisticsWindow;

    QVBoxLayout* mainLayout;
    QGridLayout* commandLayout;
    CustomTable* dogsTable;
    DogsTableModel* dogsTableModel;
    DogPictureDelegate* pictureDelegate;

    CustomButton *newDogsButton;
    CustomButton* removeButton;
    CustomButton* undoButton;
    CustomButton* redoButton;
    CustomButton* statisticsButton;
    CustomButton* seeExternallyButton;
    CustomButton *exitButton;

    QMessageBox* noDogsMessage;
    QMessageBox* selectDogMessage;

    void setUpTable();
    void setUpMainMenu();
    void initButtons();
    void openNewDogsWindow();
    void openStatisticsWindow();
public:
    explicit UserWindow(Service& service, QWidget* parent = nullptr);

signals:
    void back();
    void updateAdminTable();

};
#endif //DOG_SHELTER_USERWINDOW_H
