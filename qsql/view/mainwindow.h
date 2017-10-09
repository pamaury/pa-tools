#ifndef __main_window__
#define __main_window__

#include <QMainWindow>
#include <QtWidgets>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QSqlIndex>
#include <QSqlRecord>
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    bool setDatabase(const QString &fileName);

protected:
    //void closeEvent(QCloseEvent *event) override;

private slots:
    void tableListItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QSplitter *m_splitter;
    QListWidget *m_tablelist;
    QTableView *m_tableview;
    QSqlQueryModel m_sqlmodel;
    QSqlDatabase m_db;
}; 

#endif /* __main_window__ */
