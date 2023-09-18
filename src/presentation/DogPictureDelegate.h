#ifndef DOG_SHELTER_DOGPICTUREDELEGATE_H
#define DOG_SHELTER_DOGPICTUREDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

class DogPictureDelegate : public QStyledItemDelegate {
public:
    explicit DogPictureDelegate(QObject* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
#endif //DOG_SHELTER_DOGPICTUREDELEGATE_H
