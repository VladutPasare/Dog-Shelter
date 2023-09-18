#include "DropHereRectangle.h"

DropHereRectangle::DropHereRectangle(QWidget *parent) : QLabel(parent) {
    this->setText("Drag image here");
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("color: gray;");
}

void DropHereRectangle::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    QPen pen(Qt::gray, 2, Qt::DotLine);
    painter.setPen(pen);
    painter.drawRect(rect().adjusted(1, 1, -1, -1));
}
