#ifndef STATUSSHOW_H
#define STATUSSHOW_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>
namespace Ui {
class statusshow;
}

class statusshow : public QWidget
{
    Q_OBJECT

public:
    explicit statusshow(QWidget *parent = nullptr);
    ~statusshow();

private:
    Ui::statusshow *ui;
    QTimer t;
};

#endif // STATUSSHOW_H
