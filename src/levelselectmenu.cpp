#include "levelselectmenu.h"
#include "ui_levelselectmenu.h"
#include <QDebug>

LevelSelectMenu::LevelSelectMenu(int *p, QDialog *parent): QDialog(parent), ui(new Ui::LevelSelectMenu) {
    level = p;
    ui->setupUi(this);
    this->setWindowTitle("Select Level");
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
