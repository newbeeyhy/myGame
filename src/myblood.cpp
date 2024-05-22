#include "myblood.h"
#include <QString>
#include <QDebug>

myBlood::myBlood(myCharacter *b, QWidget *parent): myObject(parent) {
    belong = b;
    this->setPixmap(QPixmap(tr(":/blood/recourse/blood/100.png")));
    this->setGeometry(belong->X() - 27, belong->Y() + 35, 54, 8);
    this->setScaledContents(true);
    this->show();
    this->raise();
    connect(belong, &myCharacter::hpchanged, this, &myBlood::setblood);
    connect(belong, &myCharacter::poschanged, this, &myBlood::setpos);
}

void myBlood::setblood() {
    int precent = belong->pro.HP * 100 / belong->pro.maxHP;
    precent = precent - (precent & 1);
    this->setPixmap(QPixmap(QString(":/blood/recourse/blood/") + QString::number(precent) + QString(".png")));
}

void myBlood::setpos() {
    this->move(belong->X() - 27, belong->Y() + 35);
}

void myBlood::act() {

}