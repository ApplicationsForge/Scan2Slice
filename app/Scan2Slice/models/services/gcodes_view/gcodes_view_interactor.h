#ifndef GCODESVIEWINTERACTOR_H
#define GCODESVIEWINTERACTOR_H

#include <QString>
#include <QProcess>
#include <QMessageBox>
#include <QTemporaryFile>
#include <QDebug>
#include <QDir>
#include "models/settings_manager/settings_manager.h"

class GCodesViewInteractor
{
public:
    GCodesViewInteractor();

    static void execute(QStringList gcodes, QObject *parent = nullptr);
    static void execute(QString gcodesFileName, QObject *parent = nullptr);

private:
    static QString getViewerPath();
    static QString createTmpFile(QStringList gcodes);
};

#endif // GCODESVIEWINTERACTOR_H
