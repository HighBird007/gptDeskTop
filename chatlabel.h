#ifndef CHATLABEL_H
#define CHATLABEL_H

#include <QWidget>
namespace Ui {
class chatLabel;
}

class chatLabel : public QWidget
{
    Q_OBJECT

public:
    explicit chatLabel(QWidget *parent = nullptr);
    ~chatLabel();

private:
    Ui::chatLabel *ui;

};

#endif // CHATLABEL_H
