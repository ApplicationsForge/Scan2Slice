#include "read_points_from_file_interactor.h"

ReadPointsFromFileInteractor::ReadPointsFromFileInteractor()
{

}

QList<Point3D> ReadPointsFromFileInteractor::execute()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Выберите файл с точками", "", "*.txt");
    if(!QFile::exists(fileName)) return {};

    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Файл " + fileName + "не удалось открыть").exec();
        return {};
    }

    QString content = QString::fromUtf8(file.readAll());
    file.close();

    QList<Point3D> result = {};
    QStringList lines = content.split(QRegularExpression{R"-((\r\n?|\n))-"});
    for(auto line : lines)
    {
        QStringList params = line.split(" ");
        if(params.length() < 3) continue;

        Point3D p(params[0].toDouble(), params[1].toDouble(), params[2].toDouble());
        result.append(p);
    }
    return result;
}
