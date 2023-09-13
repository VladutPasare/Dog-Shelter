#include "CustomTable.h"
#include "QHeaderView"

CustomTable::CustomTable() {
    this->setFixedSize(760, 340);
    horizontalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->verticalHeader()->setDefaultSectionSize(50);
    this->verticalHeader()->setVisible(false);

    this->setStyleSheet("QTableView {"
                             "background-color: rgb(250, 250, 250);"
                             "}"
                             "QHeaderView::section {"
                             "background-color: rgb(232, 232, 230);"
                             "border: 2px solid rgb(220, 220, 220)"
                             "}"
                             "QTableView::item {"
                             "border: 2px solid rgb(220, 220, 220)"
                             "}");
}
