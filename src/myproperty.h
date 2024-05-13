#ifndef MYPROPERTY_H
#define MYPROPERTY_H

class Property {
public:
    int maxHP, HP, TATK, PATK, MATK, PDEF, MDEF, SPD, ATKF, VAL, WEI;

public:
    Property();
    Property(int maxHP_, int HP_, int TATK_, int PATK_, int MATK_, int PDEF_, int MDEF_, int SPD_, int ATKF_, int VAL_, int WEI_);
};

#endif // MYPROPERTY_H