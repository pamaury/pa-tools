#include "mainwindow.h"

MainWindow::MainWindow()
    : m_splitter(new QSplitter), m_tablelist(new QListWidget), m_tableview(new QTableView)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_tableview->setModel(&m_sqlmodel);
    auto *tablelist_box = new QGroupBox("Tables");
    auto *tablelist_layout = new QVBoxLayout;
    tablelist_layout->addWidget(m_tablelist);
    tablelist_box->setLayout(tablelist_layout);
    m_splitter->addWidget(tablelist_box);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->addWidget(m_tableview);
    m_splitter->setStretchFactor(1, 5);
    setCentralWidget(m_splitter);

    connect(m_tablelist, &QListWidget::currentItemChanged,
        this, &MainWindow::tableListItemChanged);
}

void MainWindow::tableListItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current != nullptr)
    {
        QString table = current->text();
        m_sqlmodel.setQuery(QString("SELECT * FROM %1").arg(table), m_db);
    }
    else
        m_sqlmodel.setQuery("", m_db);
}

bool MainWindow::setDatabase(const QString& filename)
{
    m_db.setDatabaseName(filename);
    if(!m_db.open())
    {
        printf("Cannot open DB '%s'\n", filename.toStdString().c_str());
        return false;
    }
    printf("DB opened\n");
    m_tablelist->clear();
    m_tablelist->addItems(m_db.tables());

    m_sqlmodel.setQuery("");
    return true;
}
