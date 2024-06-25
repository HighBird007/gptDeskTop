#ifndef CHATLABELTAG_H
#define CHATLABELTAG_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>
#include <QMenu>
class chatLabelTag : public QLabel
{
    Q_OBJECT
public:
    chatLabelTag(int,QString);
protected:
    void mouseReleaseEvent(QMouseEvent *);
protected:
    void mousePressEvent(QMouseEvent *e);
signals:
    void labelIdChange(int);
    void deleteSelf(int);
private:
    int id;
    QString content;
    QMenu *m;
};

#endif // CHATLABELTAG_H
