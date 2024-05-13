#ifndef MYBLOCK_H
#define MYBLOCK_H

#include "myobject.h"
#include <QWidget>
#include <QString>
#include <QMovie>
#include <QLabel>
#include <QMap>

class myBlock: public myObject {
    Q_OBJECT

public:
    int type;
    QString imag;
    QMovie *movie;

public:
    QMap<int, class myMonster*> monster;
    class myTower *tower = nullptr;
    
public:
    explicit myBlock(int type_, const QString &icon, QWidget *parent = nullptr);
    void play();
    void stay();
    void death();
    void act();
};

#endif // MYBLOCK_H
