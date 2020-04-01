#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "models/router.h"
#include "models/services/read_points_from_file/read_points_from_file_interactor.h"
#include "models/services/gcodes_view/gcodes_view_interactor.h"
#include "models/services/save_points_to_file/save_points_to_file_interactor.h"
#include "models/services/slice_scan/slice_scan_interactor.h"
#include "models/services/spiral_scan/spiral_scan_interactor.h"
#include "models/services/linear_scan/linear_scan_interactor.h"

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

    void on_saveToolButton_clicked();

    void on_reloadFilePushButton_clicked();

private:
    Ui::MainWindow *ui;

    void setBuildSliceWidgetsEnabled(bool enabled);
};

#endif // MAINWINDOW_H
