#ifndef CHATMAIN_H
#define CHATMAIN_H

#include <QWidget>
#include <QObject>
#include <connecttoserve.h>
#include <chatbox.h>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <chatshowwidget.h>
#include <QLabel>
#include <QScrollBar>
#include <QMovie>
#include <chatlabel.h>
#include <userchart.h>
#include <QDebug>
#include <chatlabelsshow.h>
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
    void on_pushButton_2_clicked();

private:
    Ui::chatmain *ui;
    QVBoxLayout *l;
    QSpacerItem *s;
    QStringList strlist;
    QString userchose;
    std::map<int ,chatshowwidget *> panelmap;
    int currentchatid=-1;
    chatLabelsShow *cl;
    QHBoxLayout *hl;
    QLabel *label;
        QMovie *m;
private:
     void receivehistory(QJsonObject);
     void init();
     void userChangeChat(int id);
     void userDeleteTag(int id);
 protected:
     virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // CHATMAIN_H
