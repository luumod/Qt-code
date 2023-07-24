#include "rolemodel.h"

RoleModel::RoleModel()noexcept
{
    m_role.clear();
}

void RoleModel::push_back(const QString& fileName)
{
    m_role.push_back(QPixmap(fileName));
}

void RoleModel::clear()
{
    m_role.clear();
}

bool RoleModel::isEmpty() const
{
    return m_role.isEmpty();
}

int RoleModel::size() const
{
    return m_role.size();
}

QSize RoleModel::getQSize() const
{
    return m_role[0].size();
}

QPixmap RoleModel::operator[](int index)
{
    return getAt(index);
}

QPixmap RoleModel::getAt(int index)
{
    assert(index>=0 && index<m_role.size());
    return m_role[index];
}
