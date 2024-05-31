#include "levelselectmenu.h"
#include "gamewindow.h"
#include "startmenu.h"
#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    while (1) {
        int level = 0;
        QString file = "void";
        StartMenu s(&file);
        LevelSelectMenu l(&level);
        QMediaPlayer *music = new QMediaPlayer;
        music->setMedia(QUrl("qrc:/sound/recourse/BGM/Founding Stone.mp3"));
        music->setVolume(30);
        s.show();
        music->play();
        if (s.exec() == QDialog::Accepted) {
            if (file == "void") {
                l.show();
            }
            else if (file == ""){
                continue;
            }
            else {
                music->stop();
                GameWindow g(file, level);
                g.show();
                a.exec();
                continue;
            }
        }
        else break;
        if (l.exec() == QDialog::Accepted) {
            music->stop();
            GameWindow g(file, level);
            g.show();
            a.exec();
        }
        else continue;
    }
    return 0;
}
