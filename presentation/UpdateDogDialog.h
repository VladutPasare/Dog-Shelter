#ifndef DOG_SHELTER_UPDATEDOGDIALOG_H
#define DOG_SHELTER_UPDATEDOGDIALOG_H
#include "../bussiness/Service.h"
#include "DogInfoLayout.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class UpdateDogDialog: public QDialog {
    Q_OBJECT
private:
    Service& service;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QPushButton* saveButton;
    QPushButton* cancelButton;
public:
    UpdateDogDialog(Service &service, int index, QWidget* parent = nullptr);
    signals:
        void back();
};
#endif //DOG_SHELTER_UPDATEDOGDIALOG_H
