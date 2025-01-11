#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
 

    MainWindow w; // Создаем объект главного окна
    w.show();

    return a.exec();
}
