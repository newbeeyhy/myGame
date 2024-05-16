#include "levelselectmenu.h"
#include "ui_levelselectmenu.h"

LevelSelectMenu::LevelSelectMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelSelectMenu)
{
    ui->setupUi(this);
}

LevelSelectMenu::~LevelSelectMenu()
{
    delete ui;
}
