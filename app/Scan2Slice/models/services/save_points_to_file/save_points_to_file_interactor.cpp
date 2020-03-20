#include "save_points_to_file_interactor.h"

SavePointsToFileInteractor::SavePointsToFileInteractor()
{

}

void SavePointsToFileInteractor::execute(const QList<Point3D> points, QString fileName, QString separator)
{
    if(fileName.length() <= 0)
    {
        fileName = QFileDialog::getSaveFileName(nullptr, "Выберите файл для сохранения точек", "", "*.txt");
    }
    if(fileName.length() <= 0) return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Файл " + fileName + "не удалось открыть").exec();
        return;
    }

    QString data = "";

    for(auto point : points)
    {
        data += point.toString(separator) + "\n";
    }

    file.write(data.toUtf8());
    file.close();
}
