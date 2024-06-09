#ifndef CHATSHOWWIDGET_H
#define CHATSHOWWIDGET_H

#include <QWidget>
#include <chatbox.h>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
namespace Ui {
class chatshowwidget;
}

class chatshowwidget : public QWidget
{
    Q_OBJECT

public:
    explicit chatshowwidget(QWidget *parent = nullptr);
    ~chatshowwidget();
    void addnewbox(chatbox *);
     void addnewbox(int,chatbox *);
    int getchatid();
    void setchatid(int);
    QJsonArray gethistorymess();
private:
    Ui::chatshowwidget *ui;
    QVBoxLayout *l;
    int chatid;
    std::vector<chatbox*> vec;
};

#endif // CHATSHOWWIDGET_H
