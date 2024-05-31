#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>
#include <QString>

namespace Ui {
class StartMenu;
}

class StartMenu: public QDialog {
    Q_OBJECT
    
public:
    explicit StartMenu(QString *file_, QDialog *parent = nullptr);
    ~StartMenu();

private slots:
    void on_pushButtonStartGame_clicked();
    void on_pushButtonLoadGame_clicked();
    void on_pushButtonExit_clicked();
    
private:
    QString *file = nullptr;
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
