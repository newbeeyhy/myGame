#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMouseEvent>
#include <QMediaPlayer>
#include <utility>
#include <QString>
#include <vector>
#include <string>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QFile>

namespace Ui {
class GameWindow;
}

class GameWindow: public QWidget {
    Q_OBJECT

private:
    QMediaPlayer *bgm = nullptr;
    
public:
    explicit GameWindow(QString file, int level_, QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void on_pushButtonstart_clicked();
    void on_pushButtonpause_clicked();
    void on_pushButtonsave_clicked();
    void on_pushButtonexit_clicked();
    void on_pushButtonspeed1_clicked();
    void on_pushButtonspeed2_clicked();
    void onTimer();
    void Start();
    void Stop();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    int speed = 20;
    int level = 0;
    int cost = 0;
    int hp = 5;
    int buffnum[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    int buffque[2] = {6, 0};
    int newbufftype = 0;

    Ui::GameWindow *ui;

    void InitGameWindow(int level_);
    void LoadGameWindow(QString file);

    QTimer *timer = nullptr;
    int time = 0;

    class myTower *newtower = nullptr;
    QLabel *newbuff = nullptr;
    QLabel *tower1 = nullptr;
    QLabel *tower2 = nullptr;
    QLabel *imagbuff[8];
    QLabel *numbuff[8];

    QString blockname[9];

    int pos = 0;
    int alivemonster = 0, alivetower = 0;
    QVector<std::pair<int, QString>> monsterque;
    QVector<std::pair<std::pair<int, int>, class myTower*>> towerque;

    QVector<class myBlock*> block;
    QVector<class myMonster*> monster;
    QVector<class myTower*> tower;

private:
    void Act();
    void RemoveDeath();
    void AddMonster();
    void AddTower();
    void Check();
    void SetSpeed(int x);

    friend class myMonster;
    friend class myTower;
};

#endif // GAMEWINDOW_H
