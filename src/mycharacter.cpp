#include "mycharacter.h"
#include "myblock.h"

myCharacter::myCharacter(QWidget *parent): myObject(parent) {

}

void myCharacter::play() {
    beset = true;
    movie->start();
    movief->start();
}

void myCharacter::stay() {
    movie->stop();
    movief->stop();
}

void myCharacter::death() {
    beset = false;
    movie->stop();
    movief->stop();
    if (belong != nullptr) belong->monster.remove(id);
    this->clear();
}

void myCharacter::getpro(std::string s) {
    int n = s.length(), i = 0, a[11];
    for (int j = 0; j < 11; j++) {
        int x = 0;
        while (s[i] >= '0' && s[i] <= '9' && i < n) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        i++;
        a[j] = x;
    }
    pro = Property(a[0], a[1], a[2] ,a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]);
}

void myCharacter::flip(int d) {
    if (d == 1) this->setMovie(movie);
    if (d == -1) this->setMovie(movief);
}

void myCharacter::hit(myCharacter *target) {
    cd = (cd + 1) % pro.ATKF;
    if (cd != 0) return;
    if (pro.TATK != 0) target->behit(pro.TATK, 0);
    if (pro.PATK != 0) target->behit(pro.PATK, 1);
    if (pro.MATK != 0) target->behit(pro.MATK, 2);
}

void myCharacter::behit(int damage, int type) {
    if (type == 0) {
        pro.HP = std::min(pro.maxHP, pro.HP + damage);
    }
    else if (type == 1) {
        pro.HP -= std::max(1, damage - pro.PDEF);
    }
    else if (type == 2) {
        pro.HP -= damage * (1.0 - (double)pro.MDEF / 100);
    }
    if (pro.HP <= 0) alive = false;
}