#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include <QDialog>

namespace Ui {
class LevelSelectMenu;
}

class LevelSelectMenu: public QDialog {
    Q_OBJECT

private:
    int *level;

public:
    explicit LevelSelectMenu(int *p, QDialog *parent = nullptr);
    ~LevelSelectMenu();

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    
private:
    Ui::LevelSelectMenu *ui;
};

#endif // LEVELSELECTMENU_H
