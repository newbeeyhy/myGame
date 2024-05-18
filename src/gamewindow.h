#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMouseEvent>
#include <utility>
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
    
public:
    explicit GameWindow(int level, QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void on_pushButtonstart_clicked();
    void on_pushButtonpause_clicked();
    void onTimer();
    void Start();
    void Stop();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    int cost = 0;
    int hp = 5;
    int bd = 0, fx = 0, jy = 0, kg = 0, kb = 0, qg = 0, yy = 0;

    Ui::GameWindow *ui;

    void InitGameWindow(int level);

    QTimer *timer = nullptr;
    int time = 0;

    class myTower *newtower = nullptr;
    class QLabel *tower1 = nullptr;
    class QLabel *tower2 = nullptr;

    QString blockname[9];

    int pos = 0;
    std::vector<std::pair<int, QString>> monsterque;
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

    friend class myMonster;
    friend class myTower;
};

#endif // GAMEWINDOW_H
