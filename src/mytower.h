#ifndef MYTOWER_H
#define MYTOWER_H

#include "mycharacter.h"
#include <utility>
#include <vector>
#include <string>
#include <QDebug>
#include <cmath>
#include <QFile>

class myTower: public myCharacter {
    Q_OBJECT

public:
    int type = 0;
    int cap = 0;
    std::vector<std::pair<int, int>> area;

public:
    explicit myTower(int xx, int yy, const QString &data, QWidget *parent);
    void act();
};

#endif // MYTOWER_H
