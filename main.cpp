#include <QApplication>
#include "MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return QApplication::exec();
}
