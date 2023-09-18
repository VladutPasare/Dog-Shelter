#include "CustomButton.h"

CustomButton::CustomButton(const QString& text) {
    this->setText(text);
    this->setFixedSize(200, 50);
}
