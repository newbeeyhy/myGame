#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"

myMonster::myMonster(int id_, const QString &data, QWidget *parent): myCharacter(parent) { //构造函数
    id = id_;
    belong = nullptr;
    //读取怪物文件
    QFile file(data);
    file.open(QFile::ReadOnly);
    //载入图像资源
    name = QString::fromUtf8(file.readLine()).chopped(2);
    norm = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    normf = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    attk = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    attkf = new QMovie(QString::fromUtf8(file.readLine()).chopped(2));
    this->setnowm(norm);
    //读取怪物数值
    std::string s = file.readLine().toStdString();
    getpro(s);
    //读取并设置初始位置和大小
    s = file.readLine().toStdString();
    size_t n = s.length(), i = 0;
    int a[4];
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
    //读取怪物行动路径
    s = file.readLine().toStdString();
    n = s.length();
    i = 0;
    for (int j = 0; ; j++) {
        int x = 0;
        while (s[i] >= '0' && s[i] <= '9' && i < n) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        a[j % 2] = x;
        if (j % 2 == 1) {
            path.push_back(std::make_pair(a[0] * 100 + 50, a[1] * 100 + 50));
        }
        if (s[i] == ';' || i >= n) break;
        i++;
    }
    //读取怪物攻击范围
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
    this->blood = new myBlood(this, parent);
}

int myMonster::dis() { //计算到终点的距离
    int res = 0, x = this->X(), y = this->Y();
    size_t n = path.size();
    for (size_t i = pos; i < n; i++) {
        res += abs(path[i].first - x) + abs(path[i].second - y);
        x = path[i].first;
        y = path[i].second; 
    }
    return res;
}

void myMonster::update(int type) {
    if (type == 1) { //复生
        fs = 1;
    }
    if (type == 2) { //活力
        pro.HP *= 2;
        pro.maxHP *= 2;
    }
    if (type == 3) { //坚固
        pro.PDEF *= 2;
        pro.MDEF *= 2;
    }
    if (type == 4) { //急速
        pro.SPD *= 2;
    }
    if (type == 5) { //削弱
        xr = 1;
    }
    if (type == 6) { //亡语
        wy = 1;
    }
    if (type == 7) { //隐匿
        yn = 1;
    }
    if (type == 8) { //力量
        pro.TATK *= 2;
        pro.PATK *= 2;
        pro.MATK *= 2;
    }
    if (type == 9) { //闪现
        sx = 1;
        sxcd = 0;
    }
}

void myMonster::act() { //怪物行动逻辑
    if (alive == false || beset == false) return;
    if (bd) {
        bd--;
        if (bd == 0) {
            pro.SPD *= 2;
            pro.ATKF /= 2;
            attk->setSpeed(attk->speed() * 2);
            attkf->setSpeed(attkf->speed() * 2);
            norm->setSpeed(norm->speed() * 2);
            normf->setSpeed(normf->speed() * 2);
        }
    }
    if (lx) {
        lx--;
        behit(1, 3);
    }
    if (xy) {
        xy--;
        if (xy == 0) {
            play();
        }
        return;
    }
    if (sx && sxcd != 0) {
        sxcd--;
    }
    //更新所在地块
    int bx = this->X() / 100, by = this->Y() / 100;
    if (belong != nullptr) belong->monster.remove(id);
    belong = isin->block[by * 15 + bx];
    isin->block[by * 15 + bx]->monster.insert(id, this);
    //闪现
    if (belong->tower != nullptr && sx && sxcd == 0) {
        sxcd = 250;
        if (pos >= path.size()) return;
        int x = this->X(), y = this->Y(), d = 110;
        if (abs(x - path[pos].first) < d && abs(y - path[pos].second) < d) {
            d -= (abs(x - path[pos].first) + abs(y - path[pos].second));
            Move(path[pos].first, path[pos].second);
            x = path[pos].first; y = path[pos].second;
            pos++;
        }
        int dx = (path[pos].first - x) / std::max(1, abs(path[pos].first - x)), dy = (path[pos].second - y) / std::max(1, abs(path[pos].second - y));
        if (dir != dx) {
            if (dir == 1 || dir == 0) this->setnowm(norm);
            if (dir == -1) this->setnowm(normf);
        }
        if (dx != 0) dir = dx;
        Move(x - this->width() / 2 + dx * d, y - this->height() / 2 + dy * d);
        bx = this->X() / 100; by = this->Y() / 100;
        if (belong != nullptr) belong->monster.remove(id);
        belong = isin->block[by * 15 + bx];
        isin->block[by * 15 + bx]->monster.insert(id, this);
    }
    //检测阻挡
    if (belong->tower != nullptr) {
        if (bebared == false && belong->tower->pro.WEI - belong->tower->cap >= this->pro.WEI) {
            bebared = true;
            belong->tower->bar(this);
        }
    }
    else {
        bebared = false;
    }
    myTower * itk = nullptr;
    if (bebared == false) {
        //检测攻击范围内的单位, 选取单位
        int x = this->X() / 100, y = this->Y() / 100, mn = 0x7fffffff;
        size_t m = area.size();
        for (size_t j = 0; j < m; j++) {
            int dx = area[j].first, dy = area[j].second;
            if (x + dx >= 0 && x + dx < 15 && y + dy >= 0 && y + dy < 9) {
                myBlock *u = isin->block[(y + dy) * 15 + (x + dx)];
                if (u->tower != nullptr) {
                    if (u->tower->dis(this->X(), this->Y()) < mn) {
                        mn = u->tower->dis(this->X(), this->Y());
                        itk = u->tower;
                    }
                }
            }
        }
        if (itk != nullptr) {
            if (lop >= 2 * pro.ATKF) {
                itk = nullptr;
                //沿着路径运动
                if (pos >= path.size()) return;
                int x = this->X(), y = this->Y();
                if (abs(x - path[pos].first) < pro.SPD && abs(y - path[pos].second) < pro.SPD) {
                    Move(path[pos].first, path[pos].second);
                    x = path[pos].first; y = path[pos].second;
                    pos++;
                }
                int dx = (path[pos].first - x) / std::max(1, abs(path[pos].first - x)), dy = (path[pos].second - y) / std::max(1, abs(path[pos].second - y));
                if (dir != dx) {
                    if (dir == 1 || dir == 0) this->setnowm(norm);
                    if (dir == -1) this->setnowm(normf);
                }
                if (dx != 0) dir = dx;
                Move(x - this->width() / 2 + dx * pro.SPD, y - this->height() / 2 + dy * pro.SPD);
            }
            lop = (lop + 1) % (pro.ATKF * 4);
        }
        else {
            lop = 0;
            //沿着路径运动
            if (pos >= path.size()) return;
            int x = this->X(), y = this->Y();
            if (abs(x - path[pos].first) < pro.SPD && abs(y - path[pos].second) < pro.SPD) {
                Move(path[pos].first, path[pos].second);
                x = path[pos].first; y = path[pos].second;
                pos++;
            }
            int dx = (path[pos].first - x) / std::max(1, abs(path[pos].first - x)), dy = (path[pos].second - y) / std::max(1, abs(path[pos].second - y));
            if (dir != dx) {
                if (dir == 1 || dir == 0) this->setnowm(norm);
                if (dir == -1) this->setnowm(normf);
            }
            if (dx != 0) dir = dx;
            Move(x - this->width() / 2 + dx * pro.SPD, y - this->height() / 2 + dy * pro.SPD);
        }
    }
    //选取阻挡单位进行攻击
    if (belong->tower != nullptr && bebared == true) {
        itk = belong->tower;
    }
    if (itk != nullptr) {
        if (itk->X() - this->X() < 0) dir = -1;
        if (itk->X() - this->X() > 0) dir = 1;
        if (dir == 1 || dir == 0) this->setnowm(attk);
        if (dir == -1) this->setnowm(attkf);
        hit(itk);
        if (cd == 0) {
            if (xr) {
                itk->pro.TATK /= 2;
                itk->pro.PATK /= 2;
                itk->pro.MATK /= 2;
                itk->xr = 50;
            }
        }
        if (belong->tower != nullptr && bebared == true) {
            if (belong->tower->alive == false) {
                belong->tower = nullptr;
            }
        }
    }
    else {
        if (dir == 1 || dir == 0) this->setnowm(norm);
        if (dir == -1) this->setnowm(normf);
        cd = 0;
    }
}


myMonster::~myMonster() {

}
