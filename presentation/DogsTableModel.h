#ifndef DOG_SHELTER_DOGSTABLEMODEL_H
#define DOG_SHELTER_DOGSTABLEMODEL_H
#include "../domain/Dog.h"
#include <QAbstractTableModel>
#include <vector>

class DogsTableModel : public QAbstractTableModel {
private:
    const std::vector<Dog>& dogs;
public:
    explicit DogsTableModel(const std::vector<Dog>& dogs, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const  override;
};

#endif //DOG_SHELTER_DOGSTABLEMODEL_H
