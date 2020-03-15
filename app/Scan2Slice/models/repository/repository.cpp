#include "repository.h"

Repository::Repository(QObject *parent) : QObject(parent)
{
    SettingsManager s;
    m_gCodesViewer = s.get("ExternalTools", "GCodesViewer").toString();
}

QString Repository::helloString() const
{
    return m_helloString;
}

void Repository::setHelloString(const QString &helloString)
{
    m_helloString = helloString;
}
