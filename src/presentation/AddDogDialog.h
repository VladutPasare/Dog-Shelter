#ifndef DOG_SHELTER_ADDDOGDIALOG_H
#define DOG_SHELTER_ADDDOGDIALOG_H
#include "../bussiness/Service.h"
#include "ImageDrop.h"
#include "DogInfoLayout.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

class AddDogDialog : public QDialog {
    Q_OBJECT
private:
    Service& service;
    QVBoxLayout* mainLayout;
    ImageDrop* imageDrop;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    DogInfoLayout* dogInfoLayout;
    QHBoxLayout* buttonsLayout;

    void initButtons();
    void connectSignalsAndSlots();
public:
    explicit AddDogDialog(Service& service, QWidget* parent = nullptr);
    signals:
        void back();
};

#endif //DOG_SHELTER_ADDDOGDIALOG_H
