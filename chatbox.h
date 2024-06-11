#ifndef CHATBOX_H
#define CHATBOX_H

#include <QWidget>
#include <QPixmap>
namespace Ui {
class chatbox;
}

class chatbox : public QWidget
{
    Q_OBJECT

public:
    explicit chatbox(QString content, int a, QString id, QWidget *parent = nullptr);
    explicit chatbox(QString,int);
    ~chatbox();
    QString getcontent();
    int getpeoormac();
    void appendtext(QString);
private:
    Ui::chatbox *ui;
    QString con;
    int peoormac;
    QString chatid;
};

#endif // CHATBOX_H
