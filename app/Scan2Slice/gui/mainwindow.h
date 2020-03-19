#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "models/router.h"
#include "models/services/read_points_from_file/read_points_from_file_interactor.h"
#include "models/services/gcodes_view/gcodes_view_interactor.h"
#include "models/services/scan_to_slice/scan_to_slice_interactor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updatePoints();

private slots:
    void on_openToolButton_clicked();

    void on_viewToolButton_clicked();

    void on_buildSlicePushButton_clicked();

private:
    Ui::MainWindow *ui;

    void setBuildSliceWidgetsEnabled(bool enabled);
};

#endif // MAINWINDOW_H
