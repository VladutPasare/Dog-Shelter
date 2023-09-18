#ifndef DOG_SHELTER_STATISTICSWINDOW_H
#define DOG_SHELTER_STATISTICSWINDOW_H
#include "Window.h"
#include "../bussiness/Service.h"
#include "CustomButton.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QChartView>
#include <QtCharts/QChart>
#include <QPieSeries>
#include <QTabWidget>
#include <QPushButton>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

class StatisticsWindow : public Window {
private:
    Service& service;
    QVBoxLayout* mainLayout;
    QTabWidget* tabWidget;
    QChartView* pieChartView;
    QChartView* barChartView;
    QChart* pieChart;
    QChart* barChart;
    QPieSeries* pieSeries;
    QBarSeries* barSeries;
    QBarSet* barSet;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;
    CustomButton* exitButton;

    void initButtons();
    void connectSignalsAndSlots();
public:
    explicit StatisticsWindow(Service& service, QWidget* parent = nullptr);
    void populate();
};
#endif //DOG_SHELTER_STATISTICSWINDOW_H
