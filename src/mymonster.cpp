#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"

myMonster::myMonster(int id_, const QString &data, QWidget *parent): myCharacter(parent) {
    id = id_;
    belong = nullptr;
    QFile file(data);
    file.open(QFile::ReadOnly);
    name = QString::fromUtf8(file.readLine()).chopped(2);
    movie = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    movief = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    this->setMovie(movie);
    std::string s = file.readLine().toStdString();
    getpro(s);
    s = file.readLine().toStdString();
    int n = s.length(), i = 0, a[4];
    for (int j = 0; j < 4; j++) {
        int x = 0;
        while (s[i] >= '0' && s[i] <= '9' && i < n) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        i++;
        a[j] = x;
    }
    this->setGeometry(a[0], a[1], a[2], a[3]);
    this->setScaledContents(true);
    this->show();
    s = file.readLine().toStdString();
    n = s.length(); i = 0;
    for (int j = 0; ; j++) {
        int x = 0;
        while (s[i] >= '0' && s[i] <= '9' && i < n) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        a[j % 2] = x;
        if (j % 2 == 1) {
            path.push_back(std::make_pair(a[0], a[1]));
        }
        if (s[i] == ';' || i >= n) break;
        i++;
    }
}

int myMonster::dis() {
    int res = 0, x = this->x(), y = this->y(), n = path.size();
    for (int i = pos; i < n; i++) {
        res += abs(path[i].first - x) + abs(path[i].second - y);
        x = path[i].first;
        y = path[i].second; 
    }
    return res;
}

void myMonster::act() {
    if (alive == false || beset == false) return;
    int bx = this->x() / 100, by = this->y() / 100;
    if (belong != nullptr) belong->monster.remove(id);
    belong = isin->block[by * 15 + bx];
    isin->block[by * 15 + bx]->monster.insert(id, this);
    if (belong->tower != nullptr) {
        bebared = true;
    }
    else {
        bebared = false;
    }
    if (bebared == false) {
        if (pos >= path.size()) return;
        int x = this->x(), y = this->y();
        if (abs(x - path[pos].first) < pro.SPD && abs(y - path[pos].second) < pro.SPD) {
            move(path[pos].first, path[pos].second);
            x = path[pos].first; y = path[pos].second;
            pos++;
        }
        int dx = (path[pos].first - x) / std::max(1, abs(path[pos].first - x)), dy = (path[pos].second - y) / std::max(1, abs(path[pos].second - y));
        flip(dx);
        move(x + dx * pro.SPD, y + dy * pro.SPD);
    }
    else {
        if (belong->tower != nullptr) {
            hit(belong->tower);
        }
        else cd = 0;
    }
}