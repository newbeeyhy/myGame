#include <QMessageBox>
#include "ui_gamewindow.h"
#include "mycharacter.h"
#include "gamewindow.h"
#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"

GameWindow::GameWindow(int level, QWidget *parent): QWidget(parent), ui(new Ui::GameWindow) { //构造函数
    ui->setupUi(this);
    InitGameWindow(level);
}

void GameWindow::InitGameWindow(int level) { //初始化窗口
    // 初始化计时器
    timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, GameWindow::onTimer);
    // 加载关卡文件
    this->setWindowTitle(QString("LEVEL") + QString::number(level));
    QFile file(QString("C:/YHY/work/vscode/demo/src/level/") + QString::number(level) + QString("/map.txt"));
    file.open(QFile::ReadOnly);
    // 初始化地块
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
            block[i * 15 + j]->play();
        }
    }
    // 加入icon
    tower1 = new myBlock(0, tr(":/image/recourse/tower/BloodMoonTower.gif"), this);
    tower1->setGeometry(1513, 10, 75, 93);
    tower1->setScaledContents(true);
    tower1->lower();
    tower2 = new myBlock(0, tr(":/image/recourse/spirit/Idle.gif"), this);
    tower2->setGeometry(1450, 70, 200, 200);
    tower2->setScaledContents(true);
    tower2->lower();
    // 读入初始费用
    std::string s = file.readLine().toStdString();
    int i = 0;
    while (s[i] >= '0' && s[i] <= '9' && i < s.length()) {
        cost = cost * 10 + s[i] - '0';
        i++;
    }
    ui->labelcostnum->setText(QString::number(cost));
    ui->labelhpnum->setText(QString::number(hp));
    // 载入怪物序列
    s = file.readLine().toStdString();
    int n = 0;
    i = 0;
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
    // 启动！
    on_pushButtonstart_clicked();
}

void GameWindow::on_pushButtonstart_clicked() { // 开始按钮
    Start();
    ui->pushButtonstart->setEnabled(false);
    ui->pushButtonpause->setEnabled(true);
}

void GameWindow::on_pushButtonpause_clicked() { // 暂停按钮
    Stop();
    ui->pushButtonstart->setEnabled(true);
    ui->pushButtonpause->setEnabled(false);
}

void GameWindow::Start() { //所有单位开始运动
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
        tower[i]->play();
    }
    tower1->play();
    tower2->play();
}

void GameWindow::Stop() { //所有单位停止运动
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
        tower[i]->stay();
    }
    tower1->stay();
}

void GameWindow::onTimer() { //响应计时器
    time++;
    Act();
}

void GameWindow::AddMonster() { //根据载入的怪物序列按时间顺序生成怪物
    while(pos < monsterque.size() && monsterque[pos].first == time) {
        monster.push_back(new myMonster(pos, monsterque[pos].second, this));
        monster.back()->play();
        pos++;
    }
}

void GameWindow::AddTower() { //根据玩家的摆放操作将生成防御塔
    int n = towerque.size();
    for (int i = 0; i < n; i++) {
        myTower *p = towerque[i].second;
        int bx = towerque[i].first.first, by = towerque[i].first.second;
        if (block[by * 15 + bx]->type != p->type || block[by * 15 + bx]->tower != nullptr) {
            delete p;
            continue;
        }
        cost -= p->pro.VAL;
        ui->labelcostnum->setText(QString::number(cost));
        p->play();
        tower.push_back(p);
    }
    towerque.clear();
}

void GameWindow::RemoveDeath() { //移除死亡单位
    int n;
    n = block.size();
    for (int i = 0; i < n; i++) {
        if (block[i]->alive == false && block[i]->beset == true) {
            block[i]->death();
        }
    }
    n = monster.size();
    for (int i = 0; i < n; i++) {
        if (monster[i]->alive == false && monster[i]->beset == true) {
            cost += monster[i]->pro.VAL;
            ui->labelcostnum->setText(QString::number(cost));
            monster[i]->death();
        }
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false && tower[i]->beset == true) {
            tower[i]->death();
        }
    }
}


void GameWindow::Check() { //检测和更新游戏状态
    int n = monster.size();
    for (int i = 0; i < n; i++) {
        if (monster[i]->alive == false || monster[i]->beset == false) continue;
        if (monster[i]->pos == monster[i]->path.size()) {
            hp--;
            ui->labelhpnum->setText(QString::number(hp));
            monster[i]->alive = false;
            monster[i]->death();
        }
    }
    if (hp == 0) {
        Stop();
        ui->pushButtonstart->setEnabled(false);
        ui->pushButtonpause->setEnabled(false);
        QMessageBox::information(this, tr("Game Over"), tr("You Lose!"));
        this->close();
    }
}

void GameWindow::mousePressEvent(QMouseEvent *e) { //响应鼠标点击事件，根据点击的防御塔图标生成防御塔
    int x = e->x(), y = e->y();
    if (x >= 1500 && x <= 1600 && y >= 10 && y < 110) {
        newtower = new myTower(x - 37, y - 46, tr("C:/YHY/work/vscode/demo/src/level/BloodMoonTower.txt"), this);
        newtower->play();
    }
    if (x >= 1500 && x <= 1600 && y >= 110 && y < 210) {
        newtower = new myTower(x - 100, y - 100, tr("C:/YHY/work/vscode/demo/src/level/Spirit.txt"), this);
        newtower->play();
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent *e) { //响应鼠标释放事件，根据释放位置放置防御塔
    if (newtower == nullptr) return;
    int bx = e->x() / 100, by = e->y() / 100;
    if (bx < 0 || bx >= 15 || by < 0 || by >= 9 || newtower->pro.VAL > cost) {
        delete newtower;
        newtower = nullptr;
        return;
    }
    towerque.push_back(std::make_pair(std::make_pair(bx, by), newtower));
    newtower->move(bx * 100 + (100 - newtower->width()) / 2, by * 100 + (100 - newtower->height()) / 2);
    newtower = nullptr;
}

void GameWindow::mouseMoveEvent(QMouseEvent *e) { //响应鼠标移动事件，拖动生成的防御塔到目标位置
    if (newtower == nullptr) return;
    newtower->move(e->x() - newtower->width() / 2, e->y() - newtower->height() / 2);
}

void GameWindow::Act() { //响应计时器的主逻辑，负责更新画面和单位，并调用所有单位的活动逻辑
    Check();
    RemoveDeath();
    AddMonster();
    AddTower();
    int n;
    n = block.size();
    for (int i = 0; i < n; i++) {
        block[i]->act();
    }
    n = monster.size();
    for (int i = 0; i < n; i++) {
        monster[i]->act();
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        tower[i]->act();
    }
}

GameWindow::~GameWindow() { //析构函数
    delete ui;
}