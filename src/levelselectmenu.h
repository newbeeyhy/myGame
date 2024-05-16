#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include <QWidget>

namespace Ui {
class LevelSelectMenu;
}

class LevelSelectMenu : public QWidget
{
    Q_OBJECT
    
public:
    explicit LevelSelectMenu(QWidget *parent = nullptr);
    ~LevelSelectMenu();
    
private:
    Ui::LevelSelectMenu *ui;
};

#endif // LEVELSELECTMENU_H
