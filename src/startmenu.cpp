#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QDialog *parent): QDialog(parent), ui(new Ui::StartMenu) {
    ui->setupUi(this);
    this->setWindowTitle("Start Menu");
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::on_pushButtonStartGame_clicked() {
    this->accept();
}

void StartMenu::on_pushButtonExit_clicked() {
    this->close();
}
