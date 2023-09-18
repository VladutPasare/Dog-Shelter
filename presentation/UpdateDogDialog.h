#ifndef DOG_SHELTER_UPDATEDOGDIALOG_H
#define DOG_SHELTER_UPDATEDOGDIALOG_H
#include "../bussiness/Service.h"
#include "DogInfoLayout.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include <QMessageBox>

class UpdateDogDialog: public QDialog {
    Q_OBJECT
private:
    int index;
    Dog oldDog;
    Service& service;

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QLabel* dogPhoto;
    DogInfoLayout* dogInfoLayout;
    QPushButton* saveButton;
    QPushButton* cancelButton;

    void initButtons();
    void connectSignalsAndSlots();
public:
    UpdateDogDialog(Service &service, int index, QWidget* parent = nullptr);
    signals:
        void back();
};
#endif //DOG_SHELTER_UPDATEDOGDIALOG_H
