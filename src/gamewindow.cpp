#include "ui_gamewindow.h"
#include "mycharacter.h"
#include "gamewindow.h"
#include "mymonster.h"
#include "mytower.h"
#include "myblock.h"
#include <QMessageBox>
#include <QMovie>
#include <QRandomGenerator>
#include <QFileDialog>

GameWindow::GameWindow(QString filepath, int level_, QWidget *parent): QWidget(parent), ui(new Ui::GameWindow) { //构造函数
    ui->setupUi(this);
    if (level_ != 0) InitGameWindow(level_);
    else LoadGameWindow(filepath);
}

void GameWindow::InitGameWindow(int level_) { //初始化窗口
    // 载入背景音乐
    level = level_;
    bgm = new QMediaPlayer(this);
    bgm->setMedia(QUrl("qrc:/sound/recourse/BGM/shenchizhiying.mp3"));
    bgm->setVolume(30);
    // 初始化计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::onTimer);
    // 加载关卡文件
    this->setWindowTitle(QString("LEVEL") + QString::number(level));
    QFile file(QString(":/data/level/") + QString::number(level) + QString("/map.mp"));
    file.open(QFile::ReadOnly);
    // 初始化地块
    for (int i = 0; i < 9; i++) {
        blockname[i] = QString::fromUtf8(file.readLine()).chopped(2);
    }
    for (int i = 0; i < 9; i++) {
        std::string s = file.readLine().toStdString();
        for (int j = 0; j < 15; j++) {
            int k = s[size_t(j)] - '1';
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
    size_t i = 0;
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
        s = file.readLine().toStdString();
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
    ui->kuangbaon->setText("X " + QString::number(buffnum[1]));
    imagbuff[1] = ui->kuangbao;
    numbuff[1] = ui->kuangbaon;
    ui->bingdong->setPixmap(QPixmap(tr(":/image/recourse/buff/bingdong.png")));
    ui->bingdong->setScaledContents(true);
    ui->bingdongn->setText("X " + QString::number(buffnum[2]));
    imagbuff[2] = ui->bingdong;
    numbuff[2] = ui->bingdongn;
    ui->fangxie->setPixmap(QPixmap(tr(":/image/recourse/buff/fangxie.png")));
    ui->fangxie->setScaledContents(true);
    ui->fangxien->setText("X " + QString::number(buffnum[3]));
    imagbuff[3] = ui->fangxie;
    numbuff[3] = ui->fangxien;
    ui->qungong->setPixmap(QPixmap(tr(":/image/recourse/buff/qungong.png")));
    ui->qungong->setScaledContents(true);
    ui->qungongn->setText("X " + QString::number(buffnum[4]));
    imagbuff[4] = ui->qungong;
    numbuff[4] = ui->qungongn;
    ui->jiyun->setPixmap(QPixmap(tr(":/image/recourse/buff/jiyun.png")));
    ui->jiyun->setScaledContents(true);
    ui->jiyunn->setText("X " + QString::number(buffnum[5]));
    imagbuff[5] = ui->jiyun;
    numbuff[5] = ui->jiyunn;
    ui->yingyan->setPixmap(QPixmap(tr(":/image/recourse/buff/yingyan.png")));
    ui->yingyan->setScaledContents(true);
    ui->yingyann->setText("X " + QString::number(buffnum[6]));
    imagbuff[6] = ui->yingyan;
    numbuff[6] = ui->yingyann;
    ui->kuaigong->setPixmap(QPixmap(tr(":/image/recourse/buff/kuaigong.png")));
    ui->kuaigong->setScaledContents(true);
    ui->kuaigongn->setText("X " + QString::number(buffnum[7]));
    imagbuff[7] = ui->kuaigong;
    numbuff[7] = ui->kuaigongn;
    //启动！
    ui->pushButtonspeed1->setEnabled(false);
    ui->pushButtonspeed2->setEnabled(true);
    on_pushButtonstart_clicked();
}

void GameWindow::LoadGameWindow(QString filepath) {
    //载入背景音乐
    bgm = new QMediaPlayer(this);
    bgm->setMedia(QUrl("qrc:/sound/recourse/BGM/shenchizhiying.mp3"));
    bgm->setVolume(30);
    //初始化计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::onTimer);
    //加载存档文件
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    //加载关卡编号
    std::string s = file.readLine().toStdString();
    size_t l = 0;
    int tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        level = level * 10 + s[l] - '0';
        l++;
    }
    this->setWindowTitle(QString("LEVEL") + QString::number(level));
    //加载费用
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    cost = tmp;
    ui->labelcostnum->setText(QString::number(cost));
    //加载生命值
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    hp = tmp;
    ui->labelhpnum->setText(QString::number(hp));
    //加载时间
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    time = tmp;
    //加载怪物全局buff
    s = file.readLine().toStdString();
    l = 0;
    for (int i = 0; i < 2; i++) {
        tmp = 0;
        while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
            tmp = tmp * 10 + s[l] - '0';
            l++;
        }
        buffque[i] = tmp;
        l++;
    }
    //加载我方buff数量
    s = file.readLine().toStdString();
    l = 0;
    for (int i = 0; i < 8; i++) {
        tmp = 0;
        while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
            tmp = tmp * 10 + s[l] - '0';
            l++;
        }
        buffnum[i] = tmp;
        l++;
    }
    //初始化地块
    QFile file_(QString(":/data/level/") + QString::number(level) + QString("/map.mp"));
    file_.open(QFile::ReadOnly);
    for (int i = 0; i < 9; i++) {
        blockname[i] = QString::fromUtf8(file_.readLine()).chopped(2);
    }
    for (int i = 0; i < 9; i++) {
        s = file_.readLine().toStdString();
        for (int j = 0; j < 15; j++) {
            int k = s[size_t(j)] - '1';
            if (k == 4) block.push_back(new myBlock(1, blockname[k], this));
            else block.push_back(new myBlock(2, blockname[k], this));
            block[i * 15 + j]->setGeometry(j * 100, i * 100, 100, 100);
            block[i * 15 + j]->setScaledContents(true);
            block[i * 15 + j]->lower();
            block[i * 15 + j]->play();
        }
    }
    file_.close();
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
    // 设置buff图标
    ui->kuangbao->setPixmap(QPixmap(tr(":/image/recourse/buff/kuangbao.png")));
    ui->kuangbao->setScaledContents(true);
    ui->kuangbaon->setText("X " + QString::number(buffnum[1]));
    imagbuff[1] = ui->kuangbao;
    numbuff[1] = ui->kuangbaon;
    ui->bingdong->setPixmap(QPixmap(tr(":/image/recourse/buff/bingdong.png")));
    ui->bingdong->setScaledContents(true);
    ui->bingdongn->setText("X " + QString::number(buffnum[2]));
    imagbuff[2] = ui->bingdong;
    numbuff[2] = ui->bingdongn;
    ui->fangxie->setPixmap(QPixmap(tr(":/image/recourse/buff/fangxie.png")));
    ui->fangxie->setScaledContents(true);
    ui->fangxien->setText("X " + QString::number(buffnum[3]));
    imagbuff[3] = ui->fangxie;
    numbuff[3] = ui->fangxien;
    ui->qungong->setPixmap(QPixmap(tr(":/image/recourse/buff/qungong.png")));
    ui->qungong->setScaledContents(true);
    ui->qungongn->setText("X " + QString::number(buffnum[4]));
    imagbuff[4] = ui->qungong;
    numbuff[4] = ui->qungongn;
    ui->jiyun->setPixmap(QPixmap(tr(":/image/recourse/buff/jiyun.png")));
    ui->jiyun->setScaledContents(true);
    ui->jiyunn->setText("X " + QString::number(buffnum[5]));
    imagbuff[5] = ui->jiyun;
    numbuff[5] = ui->jiyunn;
    ui->yingyan->setPixmap(QPixmap(tr(":/image/recourse/buff/yingyan.png")));
    ui->yingyan->setScaledContents(true);
    ui->yingyann->setText("X " + QString::number(buffnum[6]));
    imagbuff[6] = ui->yingyan;
    numbuff[6] = ui->yingyann;
    ui->kuaigong->setPixmap(QPixmap(tr(":/image/recourse/buff/kuaigong.png")));
    ui->kuaigong->setScaledContents(true);
    ui->kuaigongn->setText("X " + QString::number(buffnum[7]));
    imagbuff[7] = ui->kuaigong;
    numbuff[7] = ui->kuaigongn;
    //加载怪物序列
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    int n = tmp;
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    pos = tmp;
    for (int i = 0; i < n; i++) {
        s = file.readLine().toStdString();
        l = tmp = 0;
        while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
            tmp = tmp * 10 + s[l] - '0';
            l++;
        }
        QString ss = QString::fromUtf8(file.readLine()).chopped(1);
        monsterque.push_back(std::make_pair(tmp, ss));
    }
    //加载存活怪物
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    alivemonster = tmp;
    for (int i = 0; i < alivemonster; i++) {
        QString ss = QString::fromUtf8(file.readLine()).chopped(1);
        s = file.readLine().toStdString();
        l = tmp = 0;
        while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
            tmp = tmp * 10 + s[l] - '0';
            l++;
        }
        monster.push_back(new myMonster(tmp, ss, this));
        //加载怪物路径位置
        s = file.readLine().toStdString();
        l = tmp = 0;
        while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
            tmp = tmp * 10 + s[l] - '0';
            l++;
        }
        monster.back()->pos = size_t(tmp);
        //加载怪物属性
        s = file.readLine().toStdString();
        l = 0;
        for (int j = 0; j < 11; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            switch (j) {
                case 0: monster.back()->pro.maxHP = tmp; break;
                case 1: monster.back()->pro.HP = tmp; break;
                case 2: monster.back()->pro.TATK = tmp; break;
                case 3: monster.back()->pro.PATK = tmp; break;
                case 4: monster.back()->pro.MATK = tmp; break;
                case 5: monster.back()->pro.PDEF = tmp; break;
                case 6: monster.back()->pro.MDEF = tmp; break;
                case 7: monster.back()->pro.SPD = tmp; break;
                case 8: monster.back()->pro.ATKF = tmp; break;
                case 9: monster.back()->pro.VAL = tmp; break;
                case 10: monster.back()->pro.WEI = tmp; break;
            }
            l++;
        }
        monster.back()->behit(0, 0);
        //加载debuff
        s = file.readLine().toStdString();
        l = 0;
        for (int j = 0; j < 3; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            switch (j) {
                case 0: monster.back()->bd = tmp; break;
                case 1: monster.back()->lx = tmp; break;
                case 2: monster.back()->xy = tmp; break;
            }
            l++;
        }
        //加载buff
        s = file.readLine().toStdString();
        l = 0;
        for (int j = 0; j < 2; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            monster.back()->buff[j] = tmp;
            l++;
        }
        //加载cd
        s = file.readLine().toStdString();
        l = tmp = 0;
        while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
            tmp = tmp * 10 + s[l] - '0';
            l++;
        }
        monster.back()->cd = tmp;
        //加载坐标
        s = file.readLine().toStdString();
        l = 0;
        int x = 0, y = 0;
        for (int j = 0; j < 2; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            if (j == 0) x = tmp;
            else y = tmp;
            l++;
        }
        monster.back()->Move(x - monster.back()->width() / 2, y - monster.back()->height() / 2);
        monster.back()->update(monster.back()->buff[0]);
        monster.back()->update(monster.back()->buff[1]);
        monster.back()->raise();
    }
    //加载存活防御塔
    s = file.readLine().toStdString();
    l = tmp = 0;
    while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
        tmp = tmp * 10 + s[l] - '0';
        l++;
    }
    alivetower = tmp;
    for (int i = 0; i < alivetower; i++) {
        QString ss = QString::fromUtf8(file.readLine()).chopped(1);
        tower.push_back(new myTower(100, 100, ss, this));
        //加载防御塔属性
        s = file.readLine().toStdString();
        l = 0;
        for (int j = 0; j < 11; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            switch (j) {
                case 0: tower.back()->pro.maxHP = tmp; break;
                case 1: tower.back()->pro.HP = tmp; break;
                case 2: tower.back()->pro.TATK = tmp; break;
                case 3: tower.back()->pro.PATK = tmp; break;
                case 4: tower.back()->pro.MATK = tmp; break;
                case 5: tower.back()->pro.PDEF = tmp; break;
                case 6: tower.back()->pro.MDEF = tmp; break;
                case 7: tower.back()->pro.SPD = tmp; break;
                case 8: tower.back()->pro.ATKF = tmp; break;
                case 9: tower.back()->pro.VAL = tmp; break;
                case 10: tower.back()->pro.WEI = tmp; break;
            }
            l++;
        }
        tower.back()->behit(0, 0);
        //加载buff
        s = file.readLine().toStdString();
        l = 0;
        for (int j = 0; j < 2; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            tower.back()->buff[j] = tmp;
            l++;
        }
        //加载坐标
        s = file.readLine().toStdString();
        l = 0;
        int x = 0, y = 0;
        for (int j = 0; j < 2; j++) {
            tmp = 0;
            while (s[l] >= '0' && s[l] <= '9' && l < s.length()) {
                tmp = tmp * 10 + s[l] - '0';
                l++;
            }
            if (j == 0) x = tmp;
            else y = tmp;
            l++;
        }
        tower.back()->Move(x - tower.back()->width() / 2, y - tower.back()->height() / 2);
        tower.back()->update(tower.back()->buff[0]);
        tower.back()->update(tower.back()->buff[1]);
    }
    //启动！
    ui->pushButtonspeed1->setEnabled(false);
    ui->pushButtonspeed2->setEnabled(true);
    on_pushButtonstart_clicked();
}

void GameWindow::on_pushButtonstart_clicked() { //开始按钮
    Start();
    ui->pushButtonstart->setEnabled(false);
    ui->pushButtonpause->setEnabled(true);
    ui->pushButtonsave->setEnabled(false);
    ui->pushButtonexit->setEnabled(false);
}

void GameWindow::on_pushButtonpause_clicked() { //暂停按钮
    Stop();
    ui->pushButtonstart->setEnabled(true);
    ui->pushButtonpause->setEnabled(false);
    ui->pushButtonsave->setEnabled(true);
    ui->pushButtonexit->setEnabled(true);
}

void GameWindow::on_pushButtonsave_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Game"), "", tr("Game Files (*.game)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly)) {
            // Save game data here
            file.write(QString::number(level).toUtf8() + "\n");                         //关卡
            file.write(QString::number(cost).toUtf8() + "\n");                          //费用
            file.write(QString::number(hp).toUtf8() + "\n");                            //生命值
            file.write(QString::number(time).toUtf8() + "\n");                          //时间
            file.write(QString::number(buffque[0]).toUtf8() + " ");
            file.write(QString::number(buffque[1]).toUtf8() + "\n");                    //怪物全局buff
            for (int i = 0; i < 8; i++) {
                file.write(QString::number(buffnum[i]).toUtf8());                       //我方buff数量
                if (i < 7) file.write(" ");
                else file.write("\n");
            }
            int n = monsterque.size();
            file.write(QString::number(n).toUtf8() + "\n");                             //怪物序列长度
            file.write(QString::number(pos).toUtf8() + "\n");                           //怪物序列位置
            for (int i = 0; i < n; i++) {
                file.write(QString::number(monsterque[i].first).toUtf8() + "\n");        //怪物出现时间
                file.write(monsterque[i].second.toUtf8() + "\n");                       //怪物文件
            }
            n = monster.size();
            file.write(QString::number(alivemonster).toUtf8() + "\n");                  //存活怪物数
            for (int i = 0; i < n; i++) {
                if (monster[i] == nullptr || monster[i]->alive == false) continue;
                file.write(monsterque[monster[i]->id].second.toUtf8() + "\n");          //怪物文件
                file.write(QString::number(monster[i]->id).toUtf8() + "\n");            //怪物id
                file.write(QString::number(monster[i]->pos).toUtf8() + "\n");           //怪物路径位置
                file.write(QString::number(monster[i]->pro.maxHP).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.HP).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.TATK).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.PATK).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.MATK).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.PDEF).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.MDEF).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.SPD).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.ATKF).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.VAL).toUtf8() + " ");
                file.write(QString::number(monster[i]->pro.WEI).toUtf8() + "\n");       //怪物属性
                file.write(QString::number(monster[i]->bd).toUtf8() + " ");
                file.write(QString::number(monster[i]->lx).toUtf8() + " ");
                file.write(QString::number(monster[i]->xy).toUtf8() + "\n");            //debuff
                file.write(QString::number(monster[i]->buff[0]).toUtf8() + " ");
                file.write(QString::number(monster[i]->buff[1]).toUtf8() + "\n");       //buff
                file.write(QString::number(monster[i]->cd).toUtf8() + "\n");            //cd
                file.write(QString::number(monster[i]->X()).toUtf8() + " ");
                file.write(QString::number(monster[i]->Y()).toUtf8() + "\n");           //怪物坐标
            }
            n = tower.size();
            file.write(QString::number(alivetower).toUtf8() + "\n");                    //存活防御塔数
            for (int i = 0; i < n; i++) {
                if (tower[i] == nullptr || tower[i]->alive == false) continue;
                if (tower[i]->name == "BloodMoonTower") {
                    file.write(":/data/level/BloodMoonTower.twr\n");
                }
                if (tower[i]->name == "Spirit") {
                    file.write(":/data/level/Spirit.twr\n");
                }                                                                       //防御塔文件
                file.write(QString::number(tower[i]->pro.maxHP).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.HP).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.TATK).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.PATK).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.MATK).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.PDEF).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.MDEF).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.SPD).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.ATKF).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.VAL).toUtf8() + " ");
                file.write(QString::number(tower[i]->pro.WEI).toUtf8() + "\n");         //防御塔属性
                file.write(QString::number(tower[i]->buff[0]).toUtf8() + " ");
                file.write(QString::number(tower[i]->buff[1]).toUtf8() + "\n");         //buff
                file.write(QString::number(tower[i]->X()).toUtf8() + " ");
                file.write(QString::number(tower[i]->Y()).toUtf8() + "\n");             //防御塔坐标
            }
            file.close();
        }
    }
}

void GameWindow::on_pushButtonexit_clicked() {
    this->close();
}

void GameWindow::on_pushButtonspeed1_clicked() {
    SetSpeed(20);
    ui->pushButtonspeed1->setEnabled(false);
    ui->pushButtonspeed2->setEnabled(true);
}

void GameWindow::on_pushButtonspeed2_clicked() {
    SetSpeed(10);
    ui->pushButtonspeed1->setEnabled(true);
    ui->pushButtonspeed2->setEnabled(false);
}

void GameWindow::SetSpeed(int x) {
    timer->setInterval(x);
    int n;
    n = monster.size();
    for (int i = 0; i < n; i++) {
        if (monster[i]->norm != nullptr) monster[i]->norm->setSpeed(monster[i]->norm->speed() * speed / x);
        if (monster[i]->normf != nullptr) monster[i]->normf->setSpeed(monster[i]->normf->speed() * speed / x);
        if (monster[i]->attk != nullptr) monster[i]->attk->setSpeed(monster[i]->attk->speed() * speed / x);
        if (monster[i]->attkf != nullptr) monster[i]->attkf->setSpeed(monster[i]->attkf->speed() * speed / x);
        if (monster[i]->dead != nullptr) monster[i]->dead->setSpeed(monster[i]->dead->speed() * speed / x);
        if (monster[i]->deadf != nullptr) monster[i]->deadf->setSpeed(monster[i]->deadf->speed() * speed / x);
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->norm != nullptr) tower[i]->norm->setSpeed(tower[i]->norm->speed() * speed / x);
        if (tower[i]->normf != nullptr) tower[i]->normf->setSpeed(tower[i]->normf->speed() * speed / x);
        if (tower[i]->attk != nullptr) tower[i]->attk->setSpeed(tower[i]->attk->speed() * speed / x);
        if (tower[i]->attkf != nullptr) tower[i]->attkf->setSpeed(tower[i]->attkf->speed() * speed / x);
        if (tower[i]->dead != nullptr) tower[i]->dead->setSpeed(tower[i]->dead->speed() * speed / x);
        if (tower[i]->deadf != nullptr) tower[i]->deadf->setSpeed(tower[i]->deadf->speed() * speed / x);
    }
    speed = x;
}

void GameWindow::Start() { //所有单位开始运动
	timer->start(speed);
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
        alivemonster++;
        monster.push_back(new myMonster(int(pos), monsterque[pos].second, this));
        monster.back()->play();
        monster.back()->update(buffque[0]);
        monster.back()->update(buffque[1]);
        monster.back()->buff[0] = buffque[0];
        monster.back()->buff[1] = buffque[1];
        pos++;
    }
}

void GameWindow::AddTower() { //根据玩家的摆放操作将生成防御塔
    int n = towerque.size();
    for (int i = 0; i < n; i++) {
        myTower *p = towerque[i].second;
        int bx = towerque[i].first.first, by = towerque[i].first.second;
        if (block[by * 15 + bx]->type != p->type || block[by * 15 + bx]->tower != nullptr) {
            p->blood->clear();
            delete p;
            continue;
        }
        cost -= p->pro.VAL;
        ui->labelcostnum->setText(QString::number(cost));
        p->play();
        tower.push_back(p);
        alivetower++;
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
            if (monster[i]->fs == true) {
                monster[i]->alive = true;
                monster[i]->pro.HP = monster[i]->pro.maxHP; 
            }
            if (monster[i]->wy == true) {
                int x = monster[i]->X() / 100, y = monster[i]->Y() / 100;
                int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
                int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
                for (int j = 0; j < 9; j++) {
                    if (x + dx[j] >= 0 && x + dx[j] < 15 && y + dy[j] >= 0 && y + dy[j] < 9) {
                        myBlock *u = monster[i]->isin->block[(y + dy[j]) * 15 + (x + dx[j])];
                        if (u->tower != nullptr) {
                            u->tower->behit(100, 3);
                        }
                    }
                }
            }
            cost += monster[i]->pro.VAL;
            ui->labelcostnum->setText(QString::number(cost));
            monster[i]->belong->monster.remove(monster[i]->id);
            int r = QRandomGenerator::global()->bounded(100);
            if (r < 20) {
                int x = QRandomGenerator::global()->bounded(1, 8);
                buffnum[x]++;
                numbuff[x]->setText("X " + QString::number(buffnum[x]));
            }
            monster[i]->death();
            alivemonster--;
        }
    }
    n = tower.size();
    for (int i = 0; i < n; i++) {
        if (tower[i]->alive == false && tower[i]->beset == true) {
            tower[i]->belong->tower = nullptr;
            int r = QRandomGenerator::global()->bounded(100);
            if (r < 20) {
                int x = QRandomGenerator::global()->bounded(1, 10);
                if (buffque[0] == 0) {
                    buffque[0] = x;
                }
                else if (buffque[1] == 0) {
                    buffque[1] = x;
                }
                else {
                    buffque[1] = buffque[0];
                    buffque[0] = x;
                }
            }
            tower[i]->death();
            alivetower--;
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
            alivemonster--;
        }
    }
    if (hp == 0) {
        Stop();
        ui->pushButtonstart->setEnabled(false);
        ui->pushButtonpause->setEnabled(false);
        QMessageBox::information(this, tr(":-("), tr("You Lose!"));
        this->close();
    }
    if (pos == monsterque.size() && alivemonster == 0) {
        Stop();
        ui->pushButtonstart->setEnabled(false);
        ui->pushButtonpause->setEnabled(false);
        QMessageBox::information(this, tr(":-)"), tr("You Win!"));
        this->close();
    }
}

void GameWindow::mousePressEvent(QMouseEvent *e) { //响应鼠标点击事件，根据点击的防御塔图标生成防御塔
    int x = e->x(), y = e->y();
    if (x >= 1500 && x <= 1600 && y >= 20 && y < 120) {
        newtower = new myTower(x - 37, y - 46, tr(":/data/level/BloodMoonTower.twr"), this);
        newtower->play();
    }
    if (x >= 1500 && x <= 1600 && y >= 120 && y < 220) {
        newtower = new myTower(x - 100, y - 100, tr(":/data/level/Spirit.twr"), this);
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
            newtower->blood->clear();
            delete newtower;
            newtower = nullptr;
            return;
        }
        towerque.push_back(std::make_pair(std::make_pair(bx, by), newtower));
        newtower->Move(bx * 100 + (100 - newtower->width()) / 2, by * 100 + (100 - newtower->height()) / 2);
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
        newtower->Move(e->x() - newtower->width() / 2, e->y() - newtower->height() / 2);
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
