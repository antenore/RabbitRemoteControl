#ifndef CFAVORITE_H
#define CFAVORITE_H

#include <QObject>
#include "Connecter.h"

class CFavorite : public QObject
{
    Q_OBJECT
public:
    explicit CFavorite(QObject *parent = nullptr);
    
    int AddFavorite(const QString &szFil, CConnecter* pConnecter, QString szGroup);
    
signals:
    
};

#endif // CFAVORITE_H
