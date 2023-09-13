#include "DogsTableModel.h"
#include <QGradient>

DogsTableModel::DogsTableModel(const std::vector<Dog>& dogs, QObject *parent) : dogs(dogs) {}

int DogsTableModel::rowCount(const QModelIndex &parent) const {
    return dogs.size();
}

int DogsTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant DogsTableModel::data(const QModelIndex &index, int role) const {
    if(dogs.empty())
        return {};

    int row = index.row();
    int column = index.column();
    const Dog& dog = dogs[row];

    if(role == Qt::DisplayRole)

        switch(column) {
            case 1:
                return QString::fromStdString(dog.getName());
            case 2:
                return QString::fromStdString(dog.getBreed());
            case 3:
                return QString::fromStdString(std::to_string(dog.getAge()));
            case 4:
                return QString::fromStdString(dog.getPhotoLink());
            default:
                break;
        }
    return {};
}

QVariant DogsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("Image");
            case 1:
                return tr("Name");
            case 2:
                return tr("Breed:");
            case 3:
                return tr("Age");
            case 4:
                return tr("Link");
            default:
                break;
        }
    }

    return {};
}
