#ifndef FINDQTVERSION_H
#define FINDQTVERSION_H

#include <QObject>

class findQtEnv:public QObject
{
    Q_OBJECT
public:
    explicit findQtEnv(QObject* parant=nullptr);

    QStringList QtVersionList();
    QStringList QtCompilerList();

    void setQtVersion(const QString& version);
    QString qtVersion()const;
signals:
    void qtVersionChanged(const QString& version);
private:
    QString m_currentQtVersion;
    QString m_qtRootPath;
};

#endif // FINDQTVERSION_H
