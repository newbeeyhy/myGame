#include "ui_gamewindow.h"
#include "mycharacter.h"
#include "gamewindow.h"
#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"

GameWindow::GameWindow(QWidget *parent): QWidget(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);
    InitGameWindow();
}

void GameWindow::InitGameWindow() {
    timer = new QTimer(this);
    ui->labelcost->setText(QString::number(cost));
    connect(timer, QTimer::timeout, this, GameWindow::onTimer);
    this->setWindowTitle(QString("LEVEL") + QString("1"));
    QFile file(QString("C:/YHY/work/vscode/demo/src/level/") + QString("1") + QString("/map.txt"));
    file.open(QFile::ReadOnly);
    // block
    for (int i = 0; i < 9; i++) {
        blockname[i] = QString::fromUtf8(file.readLine()).chopped(2);
    }
    for (int i = 0; i < 9; i++) {
        std::string s = file.readLine().toStdString();
        for (int j = 0; j < 15; j++) {
            int k = s[j] - '1';
            if (k == 4) block.push_back(new myBlock(1, blockname[k], this));
            else block.push_back(new myBlock(2, blockname[k], this));
            block[i * 15 + j]->setGeometry(j * 100, i * 100, 100, 100);
            block[i * 15 + j]->setScaledContents(true);
            block[i * 15 + j]->lower();
            block[i * 15 + j]->beset = true;
        }
    }
    // icon
    tower1 = new myBlock(0, tr(":/image/recourse/tower/BloodMoonTower.gif"), this);
    tower1->setGeometry(1510, 10, 75, 93);
    tower1->setScaledContents(true);
    tower1->lower();
    // monster
    std::string s = file.readLine().toStdString();
    int n = 0, i = 0;
    while (s[i] >= '0' && s[i] <= '9' && i < s.length()) {
        n = n * 10 + s[i] - '0';
        i++;
    }
    for (int j = 0; j < n; j++) {
        s = file.readLine().chopped(2).toStdString();
        int x = 0;
        i = 0;
        while (s[i] >= '0' && s[i] <= '9' && i < s.length()) {
            x = x * 10 + s[i] - '0';
            i++;
        }
        QString ss = QString::fromUtf8(file.readLine()).chopped(2);
        monsterque.push_back(std::make_pair(x, ss));
    }
    on_pushButtonstart_clicked();
}

void GameWindow::on_pushButtonstart_clicked() {
    Start();
    ui->pushButtonstart->setEnabled(false);
    ui->pushButtonpause->setEnabled(true);
}

void GameWindow::on_pushButtonpause_clicked() {
    Stop();
    ui->pushButtonstart->setEnabled(true);
    ui->pushButtonpause->setEnabled(false);
}

void GameWindow::Start() {
	timer->start(20); 
    int n;
    n = block.size();
    for (int i = 0; i < n; i++) {
        block[i]->play();
    }
    n = monster.size();
    for (int i = 0; i < n; i++) {
        monster[i]->play();
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false || tower[i]->beset == false) continue;
        tower[i]->play();
    }
    tower1->play();
}

void GameWindow::Stop() {
	timer->stop();
    int n;
    n = block.size();
    for (int i = 0; i < n; i++) {
        block[i]->stay();
    }
    n = monster.size();
    for (int i = 0; i < n; i++) {
        monster[i]->stay();
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false || tower[i]->beset == false) continue;
        tower[i]->stay();
    }
    tower1->stay();
}

void GameWindow::onTimer() {
    time++;
    RemoveDeath();
    AddMonster();
    AddTower();
    Act();
}

void GameWindow::AddMonster() {
    if (pos >= monsterque.size() || monsterque[pos].first != time) return;
    monster.push_back(new myMonster(pos, monsterque[pos].second, this));
    monster.back()->beset = true;
    monster.back()->play();
    pos++;
}

void GameWindow::AddTower() {
    int n = towerque.size();
    for (int i = 0; i < n; i++) {
        myTower *p = towerque[i].second;
        int bx = towerque[i].first.first, by = towerque[i].first.second;
        if (block[by * 15 + bx]->type != p->type || block[by * 15 + bx]->tower != nullptr) {
            delete p;
            continue;
        }
        cost -= p->pro.VAL;
        ui->labelcost->setText(QString::number(cost));
        p->beset = true;
        p->play();
        tower.push_back(p);
    }
    towerque.clear();
}

void GameWindow::RemoveDeath() {
    int n;
    n = block.size();
    for (int i = 0; i < n; i++) {
        if (block[i]->alive == false && block[i]->beset == true) {
            block[i]->beset = false;
            block[i]->death();
        }
    }
    n = monster.size();
    for (int i = 0; i < n; i++) {
        if (monster[i]->alive == false && monster[i]->beset == true) {
            cost += monster[i]->pro.VAL;
            ui->labelcost->setText(QString::number(cost));
            monster[i]->beset = false;
            monster[i]->death();
        }
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false && tower[i]->beset == true) {
            tower[i]->beset = false;
            tower[i]->death();
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *e) {
    int x = e->x(), y = e->y();
    if (x >= 1510 && x <= 1585 && y >= 10 && y <= 103) {
        newtower = new myTower(x - 37, y - 46, tr("C:/YHY/work/vscode/demo/src/level/BloodMoonTower.txt"), this);
        newtower->play();
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent *e) {
    if (newtower == nullptr) return;
    int bx = e->x() / 100, by = e->y() / 100;
    if (bx < 0 || bx >= 15 || by < 0 || by >= 9 || newtower->pro.VAL > cost) {
        delete newtower;
        newtower = nullptr;
        return;
    }
    towerque.push_back(std::make_pair(std::make_pair(bx, by), newtower));
    newtower->move(bx * 100 + 12, by * 100 + 3);
    newtower = nullptr;
}

void GameWindow::mouseMoveEvent(QMouseEvent *e) {
    if (newtower == nullptr) return;
    newtower->move(e->x() - 37, e->y() - 46);
}

void GameWindow::Act() {
    int n;
    n = block.size();
    for (int i = 0; i < n; i++) {
        if (block[i]->alive == false || block[i]->beset == false) continue;
        block[i]->act();
    }
    n = monster.size();
    for (int i = 0; i < n; i++) {
        if (monster[i]->alive == false || monster[i]->beset == false) continue;
        int x = monster[i]->x() / 100, y = monster[i]->y() / 100;
        if (monster[i]->belong != nullptr) monster[i]->belong->monster.remove(monster[i]->id);
        monster[i]->belong = block[y * 15 + x];
        block[y * 15 + x]->monster.insert(monster[i]->id, monster[i]);
        monster[i]->act();
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false || tower[i]->beset == false) continue;
        if (tower[i]->belong == nullptr) {
            int x = tower[i]->x() / 100, y = tower[i]->y() / 100;
            tower[i]->belong = block[y * 15 + x];
            block[y * 15 + x]->tower = tower[i];
        }
        tower[i]->atk.clear();
        int x = tower[i]->x() / 100, y = tower[i]->y() / 100;
        int m = tower[i]->area.size();
        for (int j = 0; j < m; j++) {
            int dx = tower[i]->area[j].first, dy = tower[i]->area[j].second;
            if (x + dx >= 0 && x + dx < 15 && y + dy >= 0 && y + dy < 9) {
                tower[i]->atk.push_back(block[(y + dy) * 15 + (x + dx)]);
            }
        }
        tower[i]->act();
    }
}

GameWindow::~GameWindow() {
    delete ui;
}