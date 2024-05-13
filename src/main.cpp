#include "startmenu.h"
#include <QApplication>
#include "gamewindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    StartMenu s;
    s.show();
    if (s.exec() == QDialog::Accepted) {
        GameWindow g;
        g.show();
        return a.exec();
    }
    else return 0;
}
