#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>

namespace Ui {
class StartMenu;
}

class StartMenu: public QDialog {
    Q_OBJECT
    
public:
    explicit StartMenu(QDialog *parent = nullptr);
    ~StartMenu();

private slots:
    void on_pushButtonStartGame_clicked();
    void on_pushButtonExit_clicked();
    
private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
