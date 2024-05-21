#include "myproperty.h"

Property::Property() {
    
}

Property::Property(int maxHP_, int HP_, int TATK_, int PATK_, int MATK_, int PDEF_, int MDEF_, int SPD_, int ATKF_, int VAL_, int WEI_) {
    maxHP = maxHP_;
    HP = HP_;
    TATK = TATK_;
    PATK = PATK_;
    MATK = MATK_;
    PDEF = PDEF_;
    MDEF = MDEF_;
    SPD = SPD_; 
    ATKF = ATKF_; 
    VAL = VAL_; 
    WEI = WEI_;
}
