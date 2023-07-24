#ifndef ROLEMODEL_H
#define ROLEMODEL_H

#include <QList>
#include <QPixmap>

class RoleModel
{
public:
    RoleModel()noexcept;
    void push_back(const QString& fileName);
    void clear();
    bool isEmpty()const;
    int size()const;
    QSize getQSize()const;
public:
    QPixmap operator[](int index);
    QPixmap getAt(int index);
protected:
    QList<QPixmap> m_role;
};

#endif // ROLEMODEL_H
