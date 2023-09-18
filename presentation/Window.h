#ifndef DOG_SHELTER_WINDOW_H
#define DOG_SHELTER_WINDOW_H
#include <QWidget>
#include <QDialog>

class Window : public QWidget {
    Q_OBJECT
protected:
    explicit Window(QWidget* parent = nullptr);
    void openNewWindow(Window* newWindow);
    signals:
        void back();
};
#endif //DOG_SHELTER_WINDOW_H
