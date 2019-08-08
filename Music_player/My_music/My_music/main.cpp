#include "main_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    Main_Widget w;
    w.show();

    return a.exec();
}
