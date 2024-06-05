#include "levelselectmenu.h"
#include "ui_levelselectmenu.h"
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QDebug>

LevelSelectMenu::LevelSelectMenu(int *p, QDialog *parent): QDialog(parent), ui(new Ui::LevelSelectMenu) {
    level = p;
    ui->setupUi(this);
    this->setWindowTitle("Select Level");
    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap(tr(":/background/recourse/background/mountain.png")));
    label->setGeometry(0, 0, 816, 480);
    label->setScaledContents(true);
    label->lower();
    label->show();
}

LevelSelectMenu::~LevelSelectMenu() {
    delete ui;
}

void LevelSelectMenu::on_pushButton1_clicked() {
    *level = 1;
    this->accept();
}

void LevelSelectMenu::on_pushButton2_clicked() {
    *level = 2;
    this->accept();
}
