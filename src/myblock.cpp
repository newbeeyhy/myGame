#include "myblock.h"
#include "mytower.h"
#include "mymonster.h"

myBlock::myBlock(int type_, const QString &icon, QWidget *parent): myObject(parent) { //构造函数
    type = type_;
    imag = icon;
    movie = new QMovie(imag);
    this->setMovie(movie);
    this->show();
}

void myBlock::play() { //单位开始运行
    movie->start();
}

void myBlock::stay() { //单位暂停运行
    movie->stop();
}

void myBlock::death() { //单位死亡
    movie->stop();
    this->clear();
}

void myBlock::act() { //地块活动逻辑
    if (alive == false || beset == false) return;
}