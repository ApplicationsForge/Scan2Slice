#include "router.h"

Router::Router(QObject *parent) :
    QObject(parent),
    m_repository(this)
{
    setupConnections();
}

Router::~Router()
{
    resetConnections();
}

Router &Router::getInstance()
{
    static QScopedPointer<Router> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new Router() );
    }
    return *m_instance;
}

Repository &Router::getRepository()
{
    return m_repository;
}

void Router::setupConnections()
{

}

void Router::resetConnections()
{

}

