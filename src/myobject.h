#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QWidget>
#include <QLabel>

class myObject: public QLabel {
    Q_OBJECT

public:
    explicit myObject(QWidget *parent = nullptr);
    bool beset = false;
    bool alive = true;
    virtual void act() = 0;
};

#endif // MYOBJECT_H
