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
    explicit chatbox(QString content, int a, QWidget *parent = nullptr);
    ~chatbox();

private:
    Ui::chatbox *ui;
};

#endif // CHATBOX_H
