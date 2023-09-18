#ifndef DOG_SHELTER_USERWINDOW_H
#define DOG_SHELTER_USERWINDOW_H
#include "Window.h"
#include "NewDogsDialog.h"
#include "../bussiness/Service.h"
#include "CustomTable.h"
#include "CustomButton.h"
#include "DogsTableModel.h"
#include "DogPictureDelegate.h"
#include "StatisticsWindow.h"


class UserWindow : public Window {
    Q_OBJECT
private:
    Service& service;

    NewDogsDialog* newDogsDialog;
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
    void connectSignalsAndSlots();
public:
    explicit UserWindow(Service& service, QWidget* parent = nullptr);
    signals:
        void updateAdminTable();
};
#endif //DOG_SHELTER_USERWINDOW_H
