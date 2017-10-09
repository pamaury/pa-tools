#include <QApplication>

#include "mainwindow.h"

void usage()
{
    printf("usage: qsql <database>\n");
    exit(1);
}
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if(argc <= 1)
        usage();
    QString dbfilename(argv[1]);

    MainWindow main_win;
    main_win.setDatabase(dbfilename);
    main_win.show();
    return app.exec();

    return 0;
}
