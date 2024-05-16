#include "startmenu.h"
#include <QApplication>
#include "gamewindow.h"
#include "levelselectmenu.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int level = 0;
    StartMenu s;
    LevelSelectMenu l(&level);
    s.show();
    if (s.exec() == QDialog::Accepted) {
        l.show();
    }
    else return 0;
    if (l.exec() == QDialog::Accepted) {
        GameWindow g(level);
        g.show();
        return a.exec();
    }
    else return 0;
}
