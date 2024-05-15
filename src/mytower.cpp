#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"

myTower::myTower(int xx, int yy, const QString &data, QWidget *parent): myCharacter(parent) { //构造函数
    //读取防御塔文件
    QFile file(data);
    file.open(QFile::ReadOnly);
    //载入图像资源
    name = QString::fromUtf8(file.readLine()).chopped(2);
    norm = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    normf = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    attk = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    attkf = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    this->setnowm(norm);
    //读取防御塔数值
    std::string s = file.readLine().toStdString();
    getpro(s);
    s = file.readLine().toStdString();
    int n = s.length(), i = 0, a[2];
    while (s[i] >= '0' && s[i] <= '9' && i < n) {
        type = type * 10 + s[i] - '0';
        i++;
    }
    //读取并设置初始位置和大小
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
    //读取防御塔攻击范围
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

void myTower::bar(myMonster *p) {
    cap += p->pro.WEI;
    bared.push_back(p);
}

void myTower::act() { //防御塔活动逻辑
    if (alive == false || beset == false) return;
    this->raise();
    //更新所在地块
    if (belong == nullptr) {
        int x = this->X() / 100, y = this->Y() / 100;
        belong = isin->block[y * 15 + x];
        isin->block[y * 15 + x]->tower = this;
    }
    //优先攻击阻挡单位
    myMonster *id = nullptr;
    if (!bared.empty()) {
        id = bared.front();
        if (id->X() - this->X() < 0) dir = -1;
        if (id->X() - this->X() > 0) dir = 1;
    }
    else {
        //检测攻击范围内的单位
        atk.clear();
        int x = this->X() / 100, y = this->Y() / 100;
        int m = area.size();
        for (int j = 0; j < m; j++) {
            int dx = area[j].first, dy = area[j].second;
            if (x + dx >= 0 && x + dx < 15 && y + dy >= 0 && y + dy < 9) {
                atk.push_back(isin->block[(y + dy) * 15 + (x + dx)]);
            }
        }
        //选取单位进行攻击
        int n = atk.size(), mn = 0x7fffffff;
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
    }
    if (id != nullptr) {
        if (dir == 1) this->setnowm(attk);
        if (dir == -1) this->setnowm(attkf);
        hit(id);
        if (!bared.empty()) {
            if (bared.front()->alive == false) {
                cap -= bared.front()->pro.WEI;
                bared.pop_front();
            }
        }
        // qDebug() << (id)->pro.HP;
    }
    else {
        if (dir == 1) this->setnowm(norm);
        if (dir == -1) this->setnowm(normf);
        cd = 0;
    }
}