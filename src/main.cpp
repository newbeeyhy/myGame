#include "levelselectmenu.h"
#include "gamewindow.h"
#include "startmenu.h"
#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int level = 0;
    StartMenu s;
    LevelSelectMenu l(&level);
    QMediaPlayer *music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/sound/recourse/BGM/Founding Stone.mp3"));
    music->setVolume(30);
    s.show();
    music->play();
    if (s.exec() == QDialog::Accepted) {
        l.show();
    }
    else return 0;
    if (l.exec() == QDialog::Accepted) {
        music->stop();
        GameWindow g(level);
        g.show();
        return a.exec();
    }
    else return 0;
}
