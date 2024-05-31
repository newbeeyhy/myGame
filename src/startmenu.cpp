#include "startmenu.h"
#include "ui_startmenu.h"
#include <QFileDialog>
#include <QDebug>

StartMenu::StartMenu(QString *file_, QDialog *parent): QDialog(parent), ui(new Ui::StartMenu) {
    file = file_;
    ui->setupUi(this);
    this->setWindowTitle("Start Menu");
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
