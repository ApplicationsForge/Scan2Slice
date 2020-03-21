#include "repository.h"

Repository::Repository(QObject *parent) : QObject(parent)
{
    SettingsManager s;
    m_gCodesViewer = s.get("ExternalTools", "GCodesViewer").toString();
    m_scans = {};
}

QList<Scan> Repository::scans() const
{
    return m_scans;
}

void Repository::setScans(const QList<Scan> &scans)
{
    m_scans = scans;
}

QList<Point3D> Repository::points() const
{
    QList<Point3D> result = {};
    for(auto slice : m_scans)
    {
        result.append(slice.points());
    }
    return result;
}
