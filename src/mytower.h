#ifndef MYTOWER_H
#define MYTOWER_H

#include "mycharacter.h"
#include <utility>
#include <vector>
#include <QQueue>
#include <string>
#include <QDebug>
#include <cmath>
#include <QFile>

class myTower: public myCharacter {
    Q_OBJECT

public:
    int type = 0;
    int cap = 0;
    bool bd = false, fx = false, qg = false, jy = false, yy = false;
    std::vector<std::pair<int, int>> area;
    QQueue<class myMonster*> bared;

public:
    explicit myTower(int xx, int yy, const QString &data, QWidget *parent);
    void bar(myMonster *p);
    void act();
    int dis(int x, int y);
    void update(int type);
    ~myTower();
};

#endif // MYTOWER_H
