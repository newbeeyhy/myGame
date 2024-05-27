#ifndef MYBLOOD_H
#define MYBLOOD_H

#include "mycharacter.h"
#include "myobject.h"
#include <QPixmap>
#include <QLabel>

class myBlood: public myObject {
    Q_OBJECT

private:
    class myCharacter *belong = nullptr;

private slots:
    void setblood();
    void setpos();

public:
    explicit myBlood(myCharacter *b, QWidget *parent = nullptr);
    void act();
    ~myBlood();
};

#endif // MYBLOOD_H