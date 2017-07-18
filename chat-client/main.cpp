// Coding: UTF-8(BOM)
#if defined(_MSC_VER) && (_MSC_VER >=1600)
# pragma execution_character_set("utf-8")
#endif

#include "widget.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
