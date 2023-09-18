#include "FilterDialog.h"

FilterDialog::FilterDialog(QWidget *parent) : QDialog(parent) {
    this->setFixedSize(300, 180);
    mainLayout = new QVBoxLayout{};

    maxAgeLabel = new QLabel("Max age:");

    maxAgeLayout = new QHBoxLayout{};
    maxAgeSlider = new QSlider(Qt::Horizontal);
    maxAgeSlider->setMinimum(1);
    maxAgeSlider->setMaximum(35);
    maxAgeSlider->setValue(35);
    maxAgeSlider->setObjectName("Max Age");
    maxAgeSlider->setFixedSize(200, 30);

    setMaxAge = new QLabel{QString::fromStdString(std::to_string(maxAgeSlider->value()))};
    setMaxAge->setFixedSize(25, 25);
    setMaxAge->setAlignment(Qt::AlignCenter);
    setMaxAge->setFrameStyle(QFrame::Panel | QFrame::StyledPanel);

    maxAgeLayout->addWidget(maxAgeSlider);
    maxAgeLayout->addWidget(setMaxAge);

    breedComboBox = new QComboBox{};
    breedComboBox->setPlaceholderText("Breed");

    buttonsLayout = new QHBoxLayout{};

    okButton = new QPushButton("Ok");
    okButton->setFixedSize(100, 32);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(100, 32);

    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout->addWidget(maxAgeLabel);
    mainLayout->addItem(maxAgeLayout);
    mainLayout->addWidget(breedComboBox);
    mainLayout->addItem(buttonsLayout);
    this->setLayout(mainLayout);

    connect(maxAgeSlider, &QSlider::valueChanged, [&] () {
        setMaxAge->setText(QString::fromStdString(std::to_string(maxAgeSlider->value())));
    });

    connect(okButton, &QPushButton::clicked, this, [&] () {
        accept();
        emit setFilterData(maxAgeSlider->value(), breedComboBox->currentText().toStdString());
    });

    connect(cancelButton, &QPushButton::clicked, this, &FilterDialog::reject);
}

void FilterDialog::setBreedComboBoxData(const std::set<std::string>& breeds) {
    breedComboBox->clear();
    for(const std::string& breed : breeds)
        breedComboBox->addItem(QString::fromStdString(breed));
}
