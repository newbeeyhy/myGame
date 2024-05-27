//todo 存档
//todo 未生成的怪物
//todo 已生成的怪物（位置，属性，buff）
//todo 已放置的防御塔（位置，属性，buff）
//todo cost
//todo HP
//todo buff数量
//todo buff队列

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
