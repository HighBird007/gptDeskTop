#ifndef CHATMAIN_H
#define CHATMAIN_H

#include <QWidget>
#include <QObject>
#include <connecttoserve.h>
#include <chatbox.h>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <statusshow.h>
namespace Ui {
class chatmain;
}

class chatmain : public QWidget
{
    Q_OBJECT

public:
    explicit chatmain(QWidget *parent = nullptr);
    ~chatmain();

private slots:
    void on_pushButton_clicked();

private:
    Ui::chatmain *ui;
    QVBoxLayout *l;
    QSpacerItem *s;
    QStringList strlist;
    QString userchose;
    int offsethistory = 0;
private:
     void receivehistory(QJsonObject);
    void gethistory();
};

#endif // CHATMAIN_H
