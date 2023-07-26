#ifndef INPUTTABLEHEADER_H
#define INPUTTABLEHEADER_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class inputTableHeader;
}

class inputTableHeader : public QWidget
{
    Q_OBJECT

public:
    explicit inputTableHeader(QWidget *parent = nullptr);
    ~inputTableHeader();
    void setRow(int num);
    void setCol(int num);
    void input();
    QStringList rowHeader()const;
    QStringList colHeader()const;
signals:
    void finished();
private:
    Ui::inputTableHeader *ui;

    int m_rowCount;
    int m_colCount;

    QStringList m_rowHeader;
    QStringList m_colHeader;
};

#endif // INPUTTABLEHEADER_H
