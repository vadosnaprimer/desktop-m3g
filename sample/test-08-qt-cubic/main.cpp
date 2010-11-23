#include <QApplication>
#include "MyWidget.hpp"

int main (int argc, char* argv[])
{
    QApplication app (argc, argv);
    MyWidget* wnd = new MyWidget;
    wnd->resize (700,455);
    wnd->show();
    return app.exec();
}
