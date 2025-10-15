// main.cpp
#include <QApplication>
#include <QWidget>
#include <UI/components/main_window.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    main_window window;
    window.setWindowTitle("Qt Test Window");
    window.resize(700, 400);
    window.show();
    return app.exec();
}
