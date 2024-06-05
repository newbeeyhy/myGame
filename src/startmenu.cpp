#include "startmenu.h"
#include "ui_startmenu.h"
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QDebug>

StartMenu::StartMenu(QString *file_, QDialog *parent): QDialog(parent), ui(new Ui::StartMenu) {
    file = file_;
    ui->setupUi(this);
    this->setWindowTitle("Main Menu");
    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap(tr(":/background/recourse/background/mountain.png")));
    label->setGeometry(0, 0, 816, 480);
    label->setScaledContents(true);
    label->lower();
    label->show();
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::on_pushButtonStartGame_clicked() {
    this->accept();
}

void StartMenu::on_pushButtonLoadGame_clicked() {
    *file = QFileDialog::getOpenFileName(this, tr("Load Game"), "", tr("Game Files (*.game)"));
    this->accept();
}

void StartMenu::on_pushButtonExit_clicked() {
    this->close();
}
