#ifndef CONTRACTINFO_H
#define CONTRACTINFO_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <qrandom.h>
#include <QDebug>

//联系人的信息
class ContractInfo
{
public:
    enum Type{no,vip,svip};
    ContractInfo();
    ContractInfo(const QString& name,const QString& signature="这个人很懒，什么都没有",const QString& pixmap=":/assets/images/defaultProfile.png",const Type& type=Type(QRandomGenerator::global()->bounded(0,3)));
    ContractInfo(const ContractInfo& lhs);
    friend QDebug operator<<(QDebug out,const ContractInfo& lhs){
        out<<lhs.m_name<<lhs.m_signature<<lhs.m_type;
        return out;
    }
public:
    QString m_name;
    QString m_signature;
    QPixmap m_picture;
    Type m_type;
};

#endif // CONTRACTINFO_H
