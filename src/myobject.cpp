#include "myobject.h"

myObject::myObject(QWidget *parent): QLabel(parent) {
    isin = (GameWindow*)(parent);
}

myObject::~myObject() {
    
}