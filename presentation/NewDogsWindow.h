#ifndef DOG_SHELTER_NEWDOGSWINDOW_H
#define DOG_SHELTER_NEWDOGSWINDOW_H
#include "../bussiness/Service.h"
#include "FilterDialog.h"
#include "CustomButton.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class NewDogsWindow : public QWidget {
    Q_OBJECT
private:
    Service& service;
    Dog currentDog;

    QLabel* dogPhoto;
    QVBoxLayout* mainLayout;
    QVBoxLayout* dogDataLayout;
    QLabel* nameLabel;
    QLabel* breedLabel;
    QLabel* ageLabel;
    QGridLayout* buttonsLayout;
    CustomButton* adoptButton;
    CustomButton* skipButton;
    CustomButton* filterButton;
    CustomButton* returnButton;
    QMessageBox* noDogsMessage;
    FilterDialog* filterDialog;
    void loadImage();
public:
    explicit NewDogsWindow(Service& service, QWidget* parent = nullptr);
    void initButtons();
    void loadNextDogData();
    signals:
        void back();
        void updateTable();
};
#endif //DOG_SHELTER_NEWDOGSWINDOW_H
