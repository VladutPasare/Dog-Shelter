#ifndef DOG_SHELTER_IMAGEDROP_H
#define DOG_SHELTER_IMAGEDROP_H
#include "DropHereRectangle.h"
#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDir>

class ImageDrop : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* layout;
    QLabel* imageLabel;
    DropHereRectangle* dropHere;
    QPixmap* image;
    QString file_path;
public:
    explicit ImageDrop(QWidget* parent = nullptr);
    void save(const QString& file_name) const;
protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

};

#endif //DOG_SHELTER_IMAGEDROP_H
