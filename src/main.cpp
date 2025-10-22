// main.cpp
#include <QApplication>
#include <QWidget>
#include <UI/components/main_window.h>
#include <QDebug>

int main(int argc, char *argv[]) {
    qDebug() << "Starting application...";
    QApplication app(argc, argv);
    qDebug() << "QApplication created";

    qDebug() << "Creating main_window...";
    main_window window;
    qDebug() << "main_window created";

    window.setWindowTitle("Qt Test Window");
    window.resize(700, 400);
    window.show();
    return app.exec();
}
