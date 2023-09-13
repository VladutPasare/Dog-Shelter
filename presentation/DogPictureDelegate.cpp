#include "DogPictureDelegate.h"
#include <QPixmap>

DogPictureDelegate::DogPictureDelegate(QObject *parent) : QStyledItemDelegate(parent) {

}

void DogPictureDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if(index.column() != 0) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    auto index_name = index.model()->index(index.row(), 1);
    auto index_breed = index.model()->index(index.row(), 2);
    QString name = index.model()->data(index_name).toString();
    QString breed = index.model()->data(index_breed).toString();

    QPixmap image("../images/" + name + breed + ".png");

    if(image.isNull()) {
        std::string path = "default";
        image = QPixmap(QString::fromStdString("../images/" + path + ".png"));
    }

    painter->save();
    painter->drawPixmap(option.rect.adjusted(1, 1, -1, -1), image);
}

QSize DogPictureDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if(index.column() == 0)
        return {60, 20};
    return QStyledItemDelegate::sizeHint(option, index);
}
