#include "CustomButton.h"

CustomButton::CustomButton(const QString& text) {
    this->setFixedSize(200, 50);
    this->setText(text);
}
