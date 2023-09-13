#include "StatisticsWindow.h"
#include <QPainter>

StatisticsWindow::StatisticsWindow(Service &service, QWidget *parent) : service(service) {
    this->resize(800, 650);
    mainLayout = new QVBoxLayout{};
    tabWidget = new QTabWidget{};

    pieChart = new QChart{};
    pieChart->setTitle("Distribution of dog breeds in the shelter");

    pieSeries = new QPieSeries{};
    pieChart->addSeries(pieSeries);

    pieChartView = new QChartView{pieChart};
    pieChartView->setRenderHint(QPainter::Antialiasing);

    barChart = new QChart{};

    axisX = new QBarCategoryAxis{};
    axisY = new QValueAxis{};

    barChartView = new QChartView{barChart};
    barChartView->setRenderHint(QPainter::Antialiasing);

    tabWidget->addTab(pieChartView, "Pie Chart");
    tabWidget->addTab(barChartView, "Bar Chart");

    exitButton = new CustomButton{"Exit"};

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(exitButton);
    mainLayout->setAlignment(exitButton, Qt::AlignHCenter);
    this->setLayout(mainLayout);

    connect(exitButton, &QPushButton::clicked, this, [&] () {
        pieSeries->clear();
        barSeries->clear();
        this->close();
        back();
    });
}

void StatisticsWindow::populate() {

    barSet = new QBarSet{"Breeds"};
    barChart->removeAllSeries();
    barChart->removeAxis(axisX);
    barChart->removeAxis(axisY);
    axisX->clear();

    unsigned int maxCount = 0;
    for(const std::string& breed : service.getDogBreeds()) {
        unsigned int count = service.countDogsByBreed(breed);
        pieSeries->append(QString::fromStdString(breed), count);
        *barSet << count;
        axisX->append(QString::fromStdString(breed));

        if(count > maxCount)
            maxCount = count;
    }
    axisY->setTickCount(maxCount + 1);
    axisY->setLabelFormat("%d");
    axisY->setMax(maxCount);

    barSeries = new QBarSeries{};
    barSeries->append(barSet);
    barChart->addSeries(barSeries);

    barChart->addAxis(axisX, Qt::AlignBottom);
    barChart->addAxis(axisY, Qt::AlignLeft);
}