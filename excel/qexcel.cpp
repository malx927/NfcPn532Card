#include "qexcel.h"
#include <QFile>
#include <QMessageBox>

#define DBEXCEL "excel"

QExcel::QExcel(QObject *parent) :
    QObject(parent)
{
    columnLists.clear();
    m_sheet = "";
    m_fileName = "";
}

bool QExcel::Open(QString fileName, QString sheet)
{
        if( fileName.isEmpty() )
            return false;
        m_fileName = fileName;
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC",DBEXCEL);
        if( !db.isValid())
            return false;
        QString dsn = tr("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;DBQ=%1").arg( m_fileName );
        db.setDatabaseName(dsn);

        if( !db.open())
        {
            qDebug()<<"error";
            return false;
        }

        m_sheet = sheet;
        return GetExcelColName( );
}

bool QExcel::SaveDataFromTable(QTableWidget *tableWidget, QString fileName, QString sheet)
{
    if ( NULL == tableWidget )
    {
        return false;
    }
    QFile f(fileName);
    if ( f.exists() )
    {
        QMessageBox::warning(NULL,QString("提示:"),QString("文件已经存在,请重新输入文件名"));
        return false;
    }
 /////获取表头里的列名和列类型
    int nColCount = tableWidget->columnCount();
    QStringList columns;
    QStringList types;
    columns.clear();
    types.clear();
    for (int i=0; i<nColCount; i++)
    {
        if ( tableWidget->horizontalHeaderItem(i) != NULL )
        {
            QTableWidgetItem* item = tableWidget->horizontalHeaderItem( i );
            QString colName = item->text();
            QString colType = item->data(Qt::UserRole).toString();
            if( colType.isEmpty() )
                colType ="TEXT";
            columns.append(colName);
            types.append(colType);
        }
    }

    ////连接创建Excel文件
    QString sheetName = sheet;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","excelexport");
    if( !db.isValid())
    {
        QMessageBox::information(NULL,QString("数据库连接提示:"),db.lastError().text());
        return false;
    }
    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").arg( fileName ).arg(fileName);
    db.setDatabaseName(dsn);

    if( !db.open())
    {
        QMessageBox::information(NULL,QString("数据库连接提示:"),QString("数据库打开失败.%1").arg(db.lastError().text()));
        return false;
    }
    ///创建表
    QSqlQuery query(db);

    QString strSql = QString("CREATE TABLE [%1] (").arg(sheetName);

    for( int i = 0 ;i < columns.count();i++ )
    {
        QString strTemp = QString("%1 %2,").arg( columns.at(i) ).arg( types.at(i) );
        strSql += strTemp;
    }

    strSql.chop(1);
    strSql += ")";

    if( !query.exec( strSql))
    {
        qDebug() << query.lastError().text();
        QMessageBox::information(NULL,QString("数据库操作:"),QString("%1").arg(query.lastError().text()));
        return false;
    }
    ////写入数据
    QString values="?,";
    QString dbValues =  values.repeated( columns.count() );
    dbValues.chop(1);
    QString insertSql = QString( "INSERT INTO [%1](%2) VALUES(%3) " ).arg( sheetName ).arg( columns.join(",")).arg( dbValues );
//    qDebug() << insertSql;

    query.prepare( insertSql );

    for( int row=0 ; row < tableWidget->rowCount();row++ )
    {
        for( int col = 0;col <tableWidget->columnCount();col++ )
        {
            QString text = tableWidget->item( row,col )->text();
            query.addBindValue( text );
        }
        if( !query.exec())
        {
            QMessageBox::warning(NULL,QString("保存失败"),QString("数据导出失败,错误%1：行%2").arg(query.lastError().text()).arg( row ));
            break;
        }
    }
    ////关闭
    db.close();
    return true;
}

bool QExcel::SaveDataFromTable(QSqlQueryModel *queryModel, QString fileName, QString sheet)
{
    if ( NULL == queryModel )
    {
        return false;
    }
    QFile f(fileName);
    if ( f.exists() )
    {
        QMessageBox::warning(NULL,QString("提示:"),QString("文件已经存在,请重新输入文件名"));
        return false;
    }
 /////获取表头里的列名和列类型
   // QSqlRecord record = queryModel->record();
    int nColCount = queryModel->columnCount();
    QStringList columns;
    QStringList types;
    columns.clear();
    types.clear();
    for (int i=0; i<nColCount; i++)
    {
        QString colName = queryModel->headerData( i,Qt::Horizontal ).toString();
        QString colType ="TEXT";
        columns.append(colName);
        types.append(colType);
    }

    ////连接创建Excel文件
    QString sheetName = sheet;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","excelexport");
    if( !db.isValid())
    {
        QMessageBox::information(nullptr,QString("数据库连接提示:"),db.lastError().text());
        return false;
    }
    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").arg( fileName ).arg(fileName);
    db.setDatabaseName(dsn);

    if( !db.open())
    {
        QMessageBox::information(nullptr,QString("数据库连接提示:"),QString("数据库打开失败.%1").arg(db.lastError().text()));
        return false;
    }
    ///创建表
    QSqlQuery query(db);

    QString strSql = QString("CREATE TABLE [%1] (").arg(sheetName);

    for( int i = 0 ;i < columns.count();i++ )
    {
        QString strTemp = QString("%1 %2,").arg( columns.at(i) ).arg( types.at(i) );
        strSql += strTemp;
    }

    strSql.chop(1);
    strSql += ")";

    if( !query.exec( strSql))
    {
        qDebug() << query.lastError().text();
        QMessageBox::information(nullptr,QString("数据库操作:"),QString("%1").arg(query.lastError().text()));
        return false;
    }
    ////写入数据
    QString values="?,";
    QString dbValues =  values.repeated( columns.count() );
    dbValues.chop(1);
    QString insertSql = QString( "INSERT INTO [%1](%2) VALUES(%3) " ).arg( sheetName ).arg( columns.join(",")).arg( dbValues );
//    qDebug() << insertSql;

    query.prepare( insertSql );

    for( int row=0 ; row < queryModel->rowCount();row++ )
    {
        for( int col = 0;col <queryModel->columnCount();col++ )
        {
            QString text = queryModel->data(queryModel->index(row,col)).toString();
            query.addBindValue( text );
        }
        if( !query.exec())
        {
            QMessageBox::warning(nullptr,QString("保存失败"),QString("数据导出失败,错误%1：行%2").arg(query.lastError().text()).arg( row ));
            break;
        }
    }
    ////关闭
    db.close();
     QMessageBox::warning(nullptr,QString("保存成功"),QString("数据导出成功"));
    return true;
}

bool QExcel::ReadDataToTable(QTableWidget *tableWidget)
{
    if ( nullptr == tableWidget )
     {
         return false;
     }

    if(  m_fileName.isEmpty() || columnLists.count() == 0  )
        return false;
     //先把table的内容清空
     tableWidget->clear();
     tableWidget->setRowCount(0);
     tableWidget->setColumnCount(0);

     //重新创建表头
     tableWidget->setColumnCount(columnLists.count());
     tableWidget->setHorizontalHeaderLabels(columnLists);
    //插入新数据
     QSqlDatabase db = QSqlDatabase::database(DBEXCEL);
     QSqlQuery query( db );
     if( !query.exec(tr("select * from [%1]").arg(m_sheet)) )
         return false;

     QSqlRecord record = query.record();
     int nRow = 0 ;
     while (query.next())
     {
         tableWidget->insertRow(nRow); //插入新行
         for( int col = 0 ; col < columnLists.count(); col++ )
         {
            int fieldIndex = record.indexOf( columnLists.at(col) );
            QTableWidgetItem* item = new QTableWidgetItem( query.value(fieldIndex).toString());
            tableWidget->setItem( nRow,col,item );
         }
        nRow++;
     }

     return true;
}

bool QExcel::GetExcelColName( )
{
    columnLists.clear();
    QSqlDatabase db = QSqlDatabase::database(DBEXCEL);
    QSqlRecord record = db.record(m_sheet);
    if( record.isEmpty() )
    {
        qDebug() << "empty";
        return false;
    }

    for( int i = 0 ;i < record.count();i++ )
    {
//        qDebug() << record.field(i).type();
        columnLists.append( record.fieldName( i ) );
    }

    return columnLists.count() != 0;
}

bool QExcel::Close()
{
    {
        QSqlDatabase db = QSqlDatabase::database(DBEXCEL);
        db.close();
    }
    QSqlDatabase::removeDatabase( DBEXCEL );
    return true;
}

QStringList QExcel::getHeaderList()
{
    return columnLists;
}
