#ifndef MYCHARACTER_H
#define MYCHARACTER_H

#include "myproperty.h"
#include "myobject.h"
#include "myblood.h"
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
    int dir;
    class myBlood *blood = nullptr;
    QString name;
    QMovie *nowm = nullptr;
    QMovie *norm = nullptr, *normf = nullptr, *attk = nullptr, *attkf = nullptr, *dead = nullptr, *deadf = nullptr;
    class myBlock *belong = nullptr;
    Property pro;
    QVector<class myBlock*> atk;
    int buff[2] = {0, 0};
    int cd = 0;

signals:
    void hpchanged();
    void poschanged();

public:
    explicit myCharacter(QWidget *parent = nullptr);
    void play();
    void stay();
    void death();
    void setnowm(QMovie *m);
    void getpro(std::string s);
    void hit(myCharacter *target);
    void behit(int damage, int type);
    void Move(int x, int y);
    int X();
    int Y();
    ~myCharacter();
};

#endif // MYCHARACTER_H