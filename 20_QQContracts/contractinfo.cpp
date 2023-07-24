#include "contractinfo.h"

ContractInfo::ContractInfo()
{

}

ContractInfo::ContractInfo(const QString &name, const QString &signature, const QString &pixmap, const Type &type)
    :m_name(name),
    m_signature(signature),
    m_picture(QPixmap(pixmap)),
    m_type(type)
{

}

ContractInfo::ContractInfo(const ContractInfo &lhs)
{
    m_name=lhs.m_name;
    m_signature=lhs.m_signature;
    m_picture=lhs.m_picture;
    m_type=lhs.m_type;
}
