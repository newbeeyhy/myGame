#ifndef MYCHARACTER_H
#define MYCHARACTER_H

#include "myproperty.h"
#include "myobject.h"
#include <QWidget>
#include <QVector>
#include <QString>
#include <string>
#include <QMovie>
#include <QDebug>
#include <QLabel>
#include <QFile>

class myCharacter: public myObject {
    Q_OBJECT

public:
    int id;
    QString name;
    QMovie *movie, *movief;
    class myBlock *belong = nullptr;
    Property pro;
    int cd = 0;

public:
    explicit myCharacter(QWidget *parent = nullptr);
    void play();
    void stay();
    void death();
    void getpro(std::string s);
    void flip(int d);
    void hit(myCharacter *target);
    void behit(int damage, int type);
};

#endif // MYCHARACTER_H