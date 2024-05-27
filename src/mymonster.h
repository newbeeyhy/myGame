#ifndef MYMONSTER_H
#define MYMONSTER_H

#include "mycharacter.h"
#include <utility>
#include <vector>
#include <QDebug>
#include <string>
#include <cmath>
#include <QFile>

class myMonster: public myCharacter {
    Q_OBJECT

private:
    int fs = 0, td = 0, wy = 0, yn = 0;
    size_t pos = 0;
    std::vector<std::pair<int, int>> path;
    std::vector<std::pair<int, int>> area;

public:
    bool bebared = false;
    int lop = 0;

public:
    explicit myMonster(int id_, const QString &data, QWidget *parent);
    int dis();
    void act();
    void update(int type);
    ~myMonster();
    friend class GameWindow;
};

#endif // MYMONSTER_H
