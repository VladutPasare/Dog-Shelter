#ifndef DOG_SHELTER_NEWDOGSDIALOG_H
#define DOG_SHELTER_NEWDOGSDIALOG_H
#include "../bussiness/Service.h"
#include "FilterDialog.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class NewDogsDialog : public QDialog {
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
    QPushButton* adoptButton;
    QPushButton* skipButton;
    QPushButton* filterButton;
    QPushButton* returnButton;
    QMessageBox* noDogsMessage;
    FilterDialog* filterDialog;
    void loadImage();
public:
    explicit NewDogsDialog(Service& service, QWidget* parent= nullptr);
    void initButtons();
    void connectSignalsAndSlots();
    void loadNextDogData();
signals:
    void back();
    void updateTable();
};
#endif //DOG_SHELTER_NEWDOGSDIALOG_H
