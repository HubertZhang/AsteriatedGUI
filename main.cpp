#include "window.h"
#include <QApplication>
int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     Window* window = new Window();
    //window->showFullScreen();
     return a.exec();
}
