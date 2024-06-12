#ifndef CHATLABELTAG_H
#define CHATLABELTAG_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>
class chatLabelTag : public QLabel
{
    Q_OBJECT
public:
    chatLabelTag(int,QString);
protected:
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void labelIdChange(int);
private:
    int id;
    QString content;
};

#endif // CHATLABELTAG_H
