#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "models/router.h"
#include "models/services/read_points_from_file/read_points_from_file_interactor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openToolButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
