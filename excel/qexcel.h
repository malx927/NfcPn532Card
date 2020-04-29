#ifndef QEXCEL_H
#define QEXCEL_H

#include <QObject>
#include <QtSql>
#include <QTableWidget>



class QExcel : public QObject
{
    Q_OBJECT
public:
    explicit QExcel(QObject *parent = 0);

signals:

public slots:

public:
    bool Open(QString fileName,QString sheet = "Sheet1$");//打开xls文件
    bool SaveDataFromTable(QTableWidget *tableWidget, QString fileName,QString sheet); //保存数据到xls
    bool SaveDataFromTable(QSqlQueryModel *queryModel, QString fileName,QString sheet); //保存数据到xls
    bool ReadDataToTable(QTableWidget *tableWidget); //从xls读取数据到ui
    bool Close();
    QStringList getHeaderList();
private:
    bool GetExcelColName();
private:
    QStringList columnLists; ////保存Excel表头
    QString m_sheet; //////Excel工作薄名称
    QString m_fileName;
};

#endif // QEXCEL_H
