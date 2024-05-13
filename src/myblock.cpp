#include "myblock.h"
#include "mytower.h"
#include "mymonster.h"

myBlock::myBlock(int type_, const QString &icon, QWidget *parent): myObject(parent) {
    type = type_;
    imag = icon;
    movie = new QMovie(imag);
    this->setMovie(movie);
    this->show();
}

void myBlock::play() {
    movie->start();
}

void myBlock::stay() {
    movie->stop();
}

void myBlock::death() {
    movie->stop();
    this->clear();
}

void myBlock::act() {
    if (alive == false) return;
}