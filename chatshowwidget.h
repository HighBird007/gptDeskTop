#ifndef CHATSHOWWIDGET_H
#define CHATSHOWWIDGET_H

#include <QWidget>
#include <chatbox.h>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <unordered_map>
namespace Ui {
class chatshowwidget;
}

class chatshowwidget : public QWidget
{
    Q_OBJECT

public:
    explicit chatshowwidget(QWidget *parent = nullptr);
    ~chatshowwidget();
     void addnewbox(QString id, int,QString content);
    int getchatid();
    void setchatid(int);
    QJsonArray gethistorymess();
    void addhisbox(chatbox*);
    void adduserbox(QString);
private:
    Ui::chatshowwidget *ui;
    QVBoxLayout *l;
    int chatid;
    std::vector<chatbox*> vec;
    std::unordered_map<QString,chatbox*> umap;
};

#endif // CHATSHOWWIDGET_H
