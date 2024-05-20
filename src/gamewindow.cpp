#include "ui_gamewindow.h"
#include "mycharacter.h"
#include "gamewindow.h"
#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"
#include <QMessageBox>
#include <QMovie>
#include <QRandomGenerator>

GameWindow::GameWindow(int level, QWidget *parent): QWidget(parent), ui(new Ui::GameWindow) { //构造函数
    ui->setupUi(this);
    InitGameWindow(level);
}

void GameWindow::InitGameWindow(int level) { //初始化窗口
    // 载入背景音乐
    bgm = new QMediaPlayer(this);
    bgm->setMedia(QUrl("qrc:/sound/recourse/BGM/GameWindow.mp3"));
    bgm->setVolume(30);
    // 初始化计时器
    timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, GameWindow::onTimer);
    // 加载关卡文件
    this->setWindowTitle(QString("LEVEL") + QString::number(level));
    QFile file(QString(":/data/level/") + QString::number(level) + QString("/map.txt"));
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
    tower1 = new QLabel(this);
    tower1->setMovie(new QMovie(tr(":/image/recourse/tower/BloodMoonTower.gif")));
    tower1->setGeometry(1513, 20, 75, 93);
    tower1->setScaledContents(true);
    tower1->lower();
    tower2 = new QLabel(this);
    tower2->setMovie(new QMovie(tr(":/image/recourse/spirit/Idle.gif")));
    tower2->setGeometry(1450, 80, 200, 200);
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
    // 设置buff图标
    ui->kuangbao->setPixmap(QPixmap(tr(":/image/recourse/buff/kuangbao.png")));
    ui->kuangbao->setScaledContents(true);
    ui->kuangbao->show();
    ui->kuangbaon->setText("X " + QString::number(buffnum[1]));
    imagbuff[1] = ui->kuangbao;
    numbuff[1] = ui->kuangbaon;
    ui->bingdong->setPixmap(QPixmap(tr(":/image/recourse/buff/bingdong.png")));
    ui->bingdong->setScaledContents(true);
    ui->bingdong->show();
    ui->bingdongn->setText("X " + QString::number(buffnum[2]));
    imagbuff[2] = ui->bingdong;
    numbuff[2] = ui->bingdongn;
    ui->fangxie->setPixmap(QPixmap(tr(":/image/recourse/buff/fangxie.png")));
    ui->fangxie->setScaledContents(true);
    ui->fangxie->show();
    ui->fangxien->setText("X " + QString::number(buffnum[3]));
    imagbuff[3] = ui->fangxie;
    numbuff[3] = ui->fangxien;
    ui->qungong->setPixmap(QPixmap(tr(":/image/recourse/buff/qungong.png")));
    ui->qungong->setScaledContents(true);
    ui->qungong->show();
    ui->qungongn->setText("X " + QString::number(buffnum[4]));
    imagbuff[4] = ui->qungong;
    numbuff[4] = ui->qungongn;
    ui->jiyun->setPixmap(QPixmap(tr(":/image/recourse/buff/jiyun.png")));
    ui->jiyun->setScaledContents(true);
    ui->jiyun->show();
    ui->jiyunn->setText("X " + QString::number(buffnum[5]));
    imagbuff[5] = ui->jiyun;
    numbuff[5] = ui->jiyunn;
    ui->yingyan->setPixmap(QPixmap(tr(":/image/recourse/buff/yingyan.png")));
    ui->yingyan->setScaledContents(true);
    ui->yingyan->show();
    ui->yingyann->setText("X " + QString::number(buffnum[6]));
    imagbuff[6] = ui->yingyan;
    numbuff[6] = ui->yingyann;
    ui->kuaigong->setPixmap(QPixmap(tr(":/image/recourse/buff/kuaigong.png")));
    ui->kuaigong->setScaledContents(true);
    ui->kuaigong->show();
    ui->kuaigongn->setText("X " + QString::number(buffnum[7]));
    imagbuff[7] = ui->kuaigong;
    numbuff[7] = ui->kuaigongn;
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
    tower1->movie()->start();
    tower2->movie()->start();
    bgm->play();
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
    tower1->movie()->stop();
    tower2->movie()->stop();
    bgm->pause();
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
            monster[i]->belong->monster.remove(monster[i]->id);
            int r = QRandomGenerator::global()->bounded(100);
            if (r < 20) {
                int x = QRandomGenerator::global()->bounded(1, 8);
                buffnum[r]++;
                numbuff[r]->setText("X " + QString::number(buffnum[r]));
            }
            monster[i]->death();
        }
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false && tower[i]->beset == true) {
            tower[i]->belong->tower = nullptr;
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
    if (x >= 1500 && x <= 1600 && y >= 20 && y < 120) {
        newtower = new myTower(x - 37, y - 46, tr(":/data/level/BloodMoonTower.txt"), this);
        newtower->play();
    }
    if (x >= 1500 && x <= 1600 && y >= 120 && y < 220) {
        newtower = new myTower(x - 100, y - 100, tr(":/data/level/Spirit.txt"), this);
        newtower->play();
    }
    if (x >= 1620 && x <= 1680 && y >= 20 && y <= 100) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/kuangbao.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 1;
    }
    if (x >= 1620 && x <= 1680 && y >= 130 && y <= 190) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/bingdong.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 2;
    }
    if (x >= 1620 && x <= 1680 && y >= 240 && y <= 300) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/fangxie.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 3;
    }
    if (x >= 1620 && x <= 1680 && y >= 350 && y <= 410) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/qungong.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 4;
    }
    if (x >= 1620 && x <= 1680 && y >= 460 && y <= 520) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/jiyun.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 5;
    }
    if (x >= 1620 && x <= 1680 && y >= 570 && y <= 630) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/yingyan.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 6;
    }
    if (x >= 1620 && x <= 1680 && y >= 680 && y <= 740) {
        newbuff = new QLabel(this);
        newbuff->setGeometry(x - 30, y - 30, 60, 60);
        newbuff->setPixmap(QPixmap(tr(":/image/recourse/buff/kuaigong.png")));
        newbuff->setScaledContents(true);
        newbuff->show();
        newbufftype = 7;
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent *e) { //响应鼠标释放事件，根据释放位置放置防御塔
    if (newtower != nullptr) {
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
    if (newbuff != nullptr) {
        int bx = e->x() / 100, by = e->y() / 100;
        myTower *now = block[by * 15 + bx]->tower;
        if (bx < 0 || bx >= 15 || by < 0 || by >= 9 || now == nullptr || buffnum[newbufftype] == 0) {
            delete newbuff;
            newbuff = nullptr;
            newbufftype = 0;
            return;
        }
        if (now->buff[0] == 0) {
            now->buff[0] = newbufftype;
            now->update(newbufftype);
            buffnum[newbufftype]--;

        }
        else if (now->buff[1] == 0) {
            now->buff[1] = newbufftype;
            now->update(newbufftype);
            buffnum[newbufftype]--;

        }
        if (newbufftype == 1) ui->kuangbaon->setText("X " + QString::number(buffnum[1]));
        if (newbufftype == 2) ui->bingdongn->setText("X " + QString::number(buffnum[2]));
        if (newbufftype == 3) ui->fangxien->setText("X " + QString::number(buffnum[3]));
        if (newbufftype == 4) ui->qungongn->setText("X " + QString::number(buffnum[4]));
        if (newbufftype == 5) ui->jiyunn->setText("X " + QString::number(buffnum[5]));
        if (newbufftype == 6) ui->yingyann->setText("X " + QString::number(buffnum[6]));
        if (newbufftype == 7) ui->kuaigongn->setText("X " + QString::number(buffnum[7]));
        delete newbuff;
        newbuff = nullptr;
        newbufftype = 0;
    }
}

void GameWindow::mouseMoveEvent(QMouseEvent *e) { //响应鼠标移动事件，拖动生成的防御塔到目标位置
    if (newtower != nullptr) {
        newtower->move(e->x() - newtower->width() / 2, e->y() - newtower->height() / 2);
    }
    if (newbuff != nullptr) {
        newbuff->move(e->x() - 30, e->y() - 30);
    }
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