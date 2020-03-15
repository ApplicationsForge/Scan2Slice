#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();

    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openToolButton_clicked()
{
    try
    {
        Router &router = Router::getInstance();
        router.getRepository().setPoints(ReadPointsFromFileInteractor::execute());
        QList<Point3D> points = router.getRepository().points();

        ui->pointsTableWidget->clear();

        ui->pointsTableWidget->setRowCount(points.length());
        ui->pointsTableWidget->setColumnCount(3);

        ui->pointsTableWidget->setHorizontalHeaderLabels({"X","Y","Z"});

        for(int i = 0; i < points.length(); i++)
        {
            ui->pointsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(points[i].x())));
            ui->pointsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(points[i].y())));
            ui->pointsTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(points[i].z())));
        }

        for (int i = 0; i < ui->pointsTableWidget->columnCount(); i++)
        {
            ui->pointsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }
    catch (...)
    {
        ui->pointsTableWidget->clear();
        QMessageBox(QMessageBox::Critical, "Error", "Error").exec();
    }
}

void MainWindow::on_viewToolButton_clicked()
{
    try
    {
        Router &router = Router::getInstance();
        QList<Point3D> points = router.getRepository().points();
        QStringList gcodes = {};
        for(auto point : points)
        {
            gcodes.append(point.toGCode());
        }

        GCodesViewInteractor::execute(gcodes, this);
    }
    catch (...)
    {
        QMessageBox(QMessageBox::Critical, "Error", "Error").exec();
    }

}
