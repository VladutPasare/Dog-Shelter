#ifndef DOG_SHELTER_ADMINWINDOW_H
#define DOG_SHELTER_ADMINWINDOW_H

#include "DogsTableModel.h"
#include "../bussiness/Service.h"
#include "../bussiness/Service.h"
#include "DogPictureDelegate.h"
#include "CustomTable.h"
#include "AddDogDialog.h"
#include "UpdateDogDialog.h"
#include "CustomButton.h"

#include "Window.h"
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>

class AdminWindow : public Window {
private:
    Service& service;
    UpdateDogDialog* updateDogDialog;
    AddDogDialog* addDogDialog;
    DogPictureDelegate* pictureDelegate;
    QVBoxLayout* mainLayout;
    CustomTable* dogsTable;
    DogsTableModel* dogsTableModel;
    QGridLayout* commandLayout;
    CustomButton* addButton;
    CustomButton* removeButton;
    CustomButton* updateButton;
    CustomButton* undoButton;
    CustomButton* redoButton;
    CustomButton* exitButton;
    QMessageBox* selectDogMessage;

    void setUpMainMenu();
    void setUpTable();
    void initButtons();
    void connectSignalsAndSlots();
public:
    explicit AdminWindow(Service& service, QWidget* parent = nullptr);

public slots:
        void updateTable();

};
#endif //DOG_SHELTER_ADMINWINDOW_H
