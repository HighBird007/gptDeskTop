#ifndef CHATLABELSSHOW_H
#define CHATLABELSSHOW_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <chatlabeltag.h>
#include <QSpacerItem>
#include <unordered_set>
#include <connecttoserve.h>
namespace Ui {
class chatLabelsShow;
}

class chatLabelsShow : public QWidget
{
    Q_OBJECT

public:
    explicit chatLabelsShow(QWidget *parent = nullptr);
    ~chatLabelsShow();
    std::vector<int> initshow(QJsonObject);
private:
    Ui::chatLabelsShow *ui;
     QVBoxLayout *l;
    QVBoxLayout *scrollLay;
    QScrollArea *area;
    QWidget *w;
    QSpacerItem *space;
    std::unordered_set<int> uset;
    int maxid= 0;
private:
    void createNewLabel();
signals:
    void labelId(int);
};

#endif // CHATLABELSSHOW_H
