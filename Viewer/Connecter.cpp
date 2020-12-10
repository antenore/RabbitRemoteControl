//! @author: Kang Lin(kl222@126.com)

#include "Connecter.h"

CConnecter::CConnecter(QObject *parent) : QObject(parent),
    m_pView(new CFrmViewer())
{
    m_pView->setAttribute(Qt::WA_DeleteOnClose);
}

CFrmViewer* CConnecter::GetViewer()
{
    return m_pView;
}

QIcon CConnecter::Icon()
{
    return QIcon(":/image/Connect");
}
