#include "ConnecterSSH.h"
#include "DlgSettingsSSH.h"
#include "ConnectSSH.h"

CConnecterSSH::CConnecterSSH(CPluginViewer *parent)
    : CConnecterTerminal(parent)
{    
    m_pPara = new CParameterSSH();
    m_bThread = true;
    if(m_pPara)
    {
        m_pPara->SetPort(22);
    }
}

CConnecterSSH::~CConnecterSSH()
{}

CConnect *CConnecterSSH::InstanceConnect()
{
    return new CConnectSSH(this);
}

QDialog *CConnecterSSH::GetDialogSettings(QWidget *parent)
{
    CParameterSSH* pPara = dynamic_cast<CParameterSSH*>(GetPara());
    return new CDlgSettingsSSH(pPara, parent);
}
