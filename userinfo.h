#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QCategoryAxis>
namespace Ui {
class userInfo;
}

class userInfo : public QWidget
{
    Q_OBJECT

public:
    explicit userInfo(QWidget *parent = nullptr);
    ~userInfo();

private:
    Ui::userInfo *ui;
};

#endif // USERINFO_H
