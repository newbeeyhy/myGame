#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"

myTower::myTower(int xx, int yy, const QString &data, QWidget *parent): myCharacter(parent) {
    QFile file(data);
    file.open(QFile::ReadOnly);
    name = QString::fromUtf8(file.readLine()).chopped(2);
    movie = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    movief = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    this->setMovie(movie);
    std::string s = file.readLine().toStdString();
    getpro(s);
    s = file.readLine().toStdString();
    int n = s.length(), i = 0, a[2];
    while (s[i] >= '0' && s[i] <= '9' && i < n) {
        type = type * 10 + s[i] - '0';
        i++;
    }
    s = file.readLine().toStdString();
    n = s.length();
    i = 0;
    for (int j = 0; j < 2; j++) {
        int x = 0;
        while (s[i] >= '0' && s[i] <= '9' && i < n) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        i++;
        a[j] = x;
    }
    this->setGeometry(xx, yy, a[0], a[1]);
    this->setScaledContents(true);
    this->show();
    s = file.readLine().toStdString();
    n = s.length(); i = 0;
    for (int j = 0; ; j++) {
        int x = 0, f = 1;
        if (s[i] == '-') {
            f = -1;
            i++;
        }
        while (s[i] >= '0' && s[i] <= '9' && i < n) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        a[j % 2] = x * f;
        if (j % 2 == 1) {
            area.push_back(std::make_pair(a[0], a[1]));
        }
        if (s[i] == ';' || i >= n) break;
        i++;
    }
}

void myTower::act() {
    if (alive == false || beset == false) return;
    if (belong == nullptr) {
        int x = this->x() / 100, y = this->y() / 100;
        belong = isin->block[y * 15 + x];
        isin->block[y * 15 + x]->tower = this;
    }
    atk.clear();
    int x = this->x() / 100, y = this->y() / 100;
    int m = area.size();
    for (int j = 0; j < m; j++) {
        int dx = area[j].first, dy = area[j].second;
        if (x + dx >= 0 && x + dx < 15 && y + dy >= 0 && y + dy < 9) {
            atk.push_back(isin->block[(y + dy) * 15 + (x + dx)]);
        }
    }
    int n = atk.size(), mn = 0x7fffffff;
    myMonster *id = nullptr;
    for (int i = 0; i < n; i++) {
        myBlock *u = atk[i];
        QMap<int, myMonster*>::const_iterator it = u->monster.constBegin();
        for (; it != u->monster.constEnd(); it++) {
            if ((*it)->dis() < mn) {
                mn = (*it)->dis();
                id = *it;
            }
        }
    }
    if (id != nullptr) {
        hit(id);
        // qDebug() << (id)->pro.HP;
    }
    else cd = 0;
}