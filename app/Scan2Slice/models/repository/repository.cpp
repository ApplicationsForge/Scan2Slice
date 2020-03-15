#include "repository.h"

Repository::Repository(QObject *parent) : QObject(parent)
{
    SettingsManager s;
    m_gCodesViewer = s.get("ExternalTools", "GCodesViewer").toString();
    m_points = {};
}

QString Repository::helloString() const
{
    return m_helloString;
}

void Repository::setHelloString(const QString &helloString)
{
    m_helloString = helloString;
}

QList<Point3D> Repository::points() const
{
    return m_points;
}

void Repository::setPoints(const QList<Point3D> &points)
{
    m_points = points;
}
