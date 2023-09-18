#include "ImageDrop.h"
#include <QFile>
#include <QDir>

ImageDrop::ImageDrop(QWidget *parent) {
    this->setFixedSize(220, 220);
    setAcceptDrops(true);

    layout = new QVBoxLayout{};

    imageLabel = new QLabel();
    imageLabel->setFixedSize(220, 220);

    dropHere = new DropHereRectangle{};
    dropHere->setFixedSize(220, 220);

    this->setLayout(layout);
    layout->addWidget(dropHere);
    layout->removeWidget(dropHere);
}

void ImageDrop::dragEnterEvent(QDragEnterEvent* event) {
    if(event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1) {
        file_path = event->mimeData()->urls().first().toLocalFile();

        if(file_path.endsWith(".png") || file_path.endsWith(".jpg"))
            event->acceptProposedAction();
    }
}

void ImageDrop::dropEvent(QDropEvent *event) {
    if(event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1) {
        file_path = event->mimeData()->urls().first().toLocalFile();
        if(file_path.endsWith(".png") || file_path.endsWith(".jpg")) {
            image = new QPixmap(file_path);
            imageLabel->setPixmap(image->scaled(imageLabel->size()));
            event->acceptProposedAction();
            layout->removeWidget(dropHere);
            dropHere->hide();
            layout->addWidget(imageLabel);
        }
    }
}

void ImageDrop::save(const QString& file_name) const {
    QDir destinationDirectory("../images");
    QFile file(file_path);

    if(file.exists())
        file.rename(destinationDirectory.filePath(file_name));
}