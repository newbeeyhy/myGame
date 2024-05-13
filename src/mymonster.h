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
    int pos = 0;
    std::vector<std::pair<int, int>> path;

public:
    bool bebared = false;

public:
    explicit myMonster(int id_, const QString &data, QWidget *parent);
    int dis();
    void act();
};

#endif // MYMONSTER_H
