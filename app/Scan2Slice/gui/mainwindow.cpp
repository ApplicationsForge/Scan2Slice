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

    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePoints()
{
    Router &router = Router::getInstance();
    QList<Point3D> points = router.getRepository().points();


    ui->pointsTableWidget->clear();

    ui->pointsTableWidget->setRowCount(points.length());
    ui->pointsTableWidget->setColumnCount(3);

    ui->pointsTableWidget->setHorizontalHeaderLabels({"X","Y","Z"});

    for(int i = 0; i < points.length(); i++)
    {
        ui->pointsTableWidget->setItem(i, 0, new QTableWidgetItem(points[i].getX()));
        ui->pointsTableWidget->setItem(i, 1, new QTableWidgetItem(points[i].getY()));
        ui->pointsTableWidget->setItem(i, 2, new QTableWidgetItem(points[i].getZ()));
    }

    for (int i = 0; i < ui->pointsTableWidget->columnCount(); i++)
    {
        ui->pointsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

void MainWindow::on_openToolButton_clicked()
{
    try
    {
        Router &router = Router::getInstance();
        router.getRepository().setOpenedFileName("");
        this->on_reloadFilePushButton_clicked();
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

void MainWindow::on_buildSlicePushButton_clicked()
{
    try
    {
        double distanceFromLaser = ui->distanceLineEdit->text().toDouble();
        double step = ui->stepLineEdit->text().toDouble();
        double generalRotationAngle = ui->rotationAngleLineEdit->text().toDouble();

        switch(ui->scanTypeTabWidget->currentIndex())
        {
        case 0:
        {
            double spiralCorrectionAngle = ui->spiralCorrectionAngleLineEdit->text().toDouble();
            SpiralScanInteractor::execute(distanceFromLaser, step, generalRotationAngle, spiralCorrectionAngle);
            break;
        }
        case 1:
        {
            bool useRotationFix = ui->rotationFixCheckBox->isChecked();
            double toleranceX = ui->toleranceXLineEdit->text().toDouble();
            SliceScanInteractor::execute(distanceFromLaser, step, toleranceX, generalRotationAngle, useRotationFix);
            break;
        }
        case 2:
        {
            bool snakeSplit = ui->snakeScanCheckBox->isChecked();
            if(snakeSplit)
            {
                LinearScanInteractor::execute(distanceFromLaser, step, generalRotationAngle);
            }
            else
            {
                double toleranceY = ui->toleranceYLineEdit->text().toDouble();
                LinearScanInteractor::execute(distanceFromLaser, step, toleranceY, generalRotationAngle);
            }
            break;
        }
        }

        this->updatePoints();
        this->setBuildSliceWidgetsEnabled(false);
    }
    catch (...)
    {
        QMessageBox(QMessageBox::Critical, "Error", "Error").exec();
    }
}

void MainWindow::setBuildSliceWidgetsEnabled(bool enabled)
{
    ui->buildSlicePushButton->setEnabled(enabled);
}

void MainWindow::on_saveToolButton_clicked()
{
    Router& router = Router::getInstance();
    SavePointsToFileInteractor::execute(router.getRepository().points(), "", " ");
}

void MainWindow::on_reloadFilePushButton_clicked()
{
    try
    {
        Router &router = Router::getInstance();
        router.getRepository().setScans({ Scan(ReadPointsFromFileInteractor::execute(router.getRepository().openedFileName())) });
        this->updatePoints();
        this->setBuildSliceWidgetsEnabled(true);
    }
    catch (...)
    {
        ui->pointsTableWidget->clear();
        QMessageBox(QMessageBox::Critical, "Error", "Error").exec();
    }
}

void MainWindow::on_snakeScanCheckBox_clicked()
{
    bool state = ui->snakeScanCheckBox->isChecked();
    ui->toleranceYLabel->setEnabled(!state);
    ui->toleranceYLineEdit->setEnabled(!state);
}
