#ifndef MYOBJECT_H
#define MYOBJECT_H

#include "gamewindow.h"
#include <QWidget>
#include <QLabel>

class myObject: public QLabel {
    Q_OBJECT

public:
    explicit myObject(QWidget *parent = nullptr);
    bool beset = false;
    bool alive = true;
    class GameWindow *isin = nullptr;
    virtual void act() = 0;
};

#endif // MYOBJECT_H
