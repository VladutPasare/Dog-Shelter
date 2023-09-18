#ifndef DOG_SHELTER_DROPHERERECTANGLE_H
#define DOG_SHELTER_DROPHERERECTANGLE_H
#include <QLabel>
#include <QPainter>

class DropHereRectangle : public QLabel {
    Q_OBJECT
public:
    explicit DropHereRectangle(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
};
#endif //DOG_SHELTER_DROPHERERECTANGLE_H
