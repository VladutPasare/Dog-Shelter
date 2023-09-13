#ifndef DOG_SHELTER_FILTERDIALOG_H
#define DOG_SHELTER_FILTERDIALOG_H
#include <set>
#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

class FilterDialog : public QDialog {
    Q_OBJECT
private:

    QVBoxLayout* mainLayout;
    QHBoxLayout* maxAgeLayout;
    QHBoxLayout* buttonsLayout;
    QLabel* maxAgeLabel;
    QLabel* setMaxAge;
    QSlider* maxAgeSlider;
    QComboBox* breedComboBox;
    QPushButton* okButton;
    QPushButton* cancelButton;
public:
    explicit FilterDialog(QWidget* parent = nullptr);
    ~FilterDialog();
    void setBreedComboBoxData(const std::set<std::string>& breeds);
    signals:
        void setFilterData(int maxAge, const std::string& breed);
};

#endif //DOG_SHELTER_FILTERDIALOG_H
