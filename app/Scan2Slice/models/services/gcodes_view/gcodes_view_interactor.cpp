#include "gcodes_view_interactor.h"

GCodesViewInteractor::GCodesViewInteractor()
{

}

void GCodesViewInteractor::execute(QStringList gcodes, QObject* parent)
{
    if(gcodes.length() > 100)
    {
        try
        {
            GCodesViewInteractor::execute(createTmpFile(gcodes), parent);
        }
        catch(std::runtime_error e)
        {
            qDebug() << e.what();
            return;
        }
    }
    else
    {
        QStringList args = {"-i", gcodes.join("\r\n")};
        QProcess* viewProcess = new QProcess(parent);
        QObject::connect(viewProcess, SIGNAL(finished(int)), viewProcess, SLOT(deleteLater()));
        viewProcess->start(getViewerPath(), args);
    }
}

void GCodesViewInteractor::execute(QString gcodesFileName, QObject* parent)
{
    QStringList args = {"-f", gcodesFileName};
    QProcess* viewProcess = new QProcess(parent);
    QObject::connect(viewProcess, SIGNAL(finished(int)), viewProcess, SLOT(deleteLater()));
    viewProcess->start(getViewerPath(), args);
}

QString GCodesViewInteractor::getViewerPath()
{
    QString gcodesViewerPath = "";

    SettingsManager s = SettingsManager();
    gcodesViewerPath = s.get("ExternalTools", "GCodesViewer").toString();

    return gcodesViewerPath;
}

QString GCodesViewInteractor::createTmpFile(QStringList gcodes)
{
    QString data = gcodes.join("\r\n");

    QDir currentDir = QDir::current();
    QString tmpFileName = currentDir.filePath("pointsAsGCodes.txt");
    QFile file(tmpFileName);

    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        throw std::runtime_error("can not create tmp file");
    }

    file.write(data.toUtf8());
    file.close();

    return file.fileName();
}
