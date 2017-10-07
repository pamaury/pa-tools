#include <QApplication>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlIndex>
#include <QSqlRecord>
#include <QDir>
#include <QFile>

void usage()
{
    printf("usage: qsql <database> [<output prefix>]\n");
    exit(1);
}

void dump_table(QSqlDatabase& db, const QString& table)
{
    printf("===== %s =====\n", table.toLocal8Bit().data());
    QSqlQuery query("SELECT * FROM " + table, db);
    QSqlRecord record = query.record();
    QStringList fields;
    for(int i = 0; i < record.count(); i++)
        fields.append(record.fieldName(i));
    for(int i = 0; i < fields.size(); i++)
        printf("%s ", fields[i].toLocal8Bit().data());
    printf("\n");
    while(query.next())
    {
        for(int i = 0; i < fields.size(); i++)
            printf("%s ", query.value(i).toString().toLocal8Bit().data());
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if(argc <= 1)
        usage();
    QString dbfilename(argv[1]);
    bool has_out = false;
    QDir output_prefix;
    if(argc >= 3)
    {
        has_out = true;
        output_prefix = QDir(argv[2]);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
 
    db.setDatabaseName(dbfilename);
    if(!db.open())
    {
        printf("Cannot open DB\n");
        return 1;
    }
    printf("DB opened\n");
    printf("Tables:\n");
    QStringList list = db.tables();
    //for(int i = 0; i < list.size(); i++)
    //    dump_table(db, list[i]);

    QSqlQuery query("SELECT * FROM FileTable", db);
    int i_keyword = query.record().indexOf("keyword");
    int i_filename = query.record().indexOf("FileName");
    int i_filelen = query.record().indexOf("FileLength");
    int i_file = query.record().indexOf("File");

    QSqlQuery attr_query("SELECT FilePath,FileTime FROM FileAttribute WHERE Keyword=? AND FileName=?", db);

    while(query.next())
    {
        QString keyword = query.value(i_keyword).toString();
        QString filename = query.value(i_filename).toString();
        unsigned filelen = query.value(i_filelen).toUInt();
        QVariant filecontent = query.value(i_file);

        attr_query.bindValue(0, keyword);
        attr_query.bindValue(1, filename);
        attr_query.exec();
        int i_path = attr_query.record().indexOf("FilePath");
        int i_time = attr_query.record().indexOf("FileTime");
        QString file_path;
        QString file_time;
        if(attr_query.next())
        {
            file_path = attr_query.value(i_path).toString();
            file_time = attr_query.value(i_time).toString();
        }

        printf("File: %s (Keyword = %s, Length = %u, Path = %s, Time = %s)\n",
            filename.toLocal8Bit().data(), keyword.toLocal8Bit().data(), filelen,
            file_path.toLocal8Bit().data(), file_time.toLocal8Bit().data());
        if(has_out)
        {
            QDir dir = QDir(output_prefix);
            if(!dir.exists(keyword))
                dir.mkdir(keyword);
            dir.cd(keyword);
            QFile file(dir.filePath(filename));
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);
            file.write(filecontent.toByteArray());
            file.close();
        }
    }

    return 0;
} 
