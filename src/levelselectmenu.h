#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include <Qdialog>

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
    
private:
    Ui::LevelSelectMenu *ui;
};

#endif // LEVELSELECTMENU_H
