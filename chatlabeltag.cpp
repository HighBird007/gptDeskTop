#include "chatlabeltag.h"

chatLabelTag::chatLabelTag(int a,QString c) {
    id =a;
    content = c;
    m =new QMenu(this);
    this->setText(content);
    this->setFixedSize(QSize(180,80));
    this->setStyleSheet("border: 1px solid black; margin: 5px; padding: 5px;");
    QAction *d = new QAction("delete",this);
    connect(d,&QAction::triggered,this,[=](){
        emit deleteSelf(id);
    });
    m->addAction(d);
}

void chatLabelTag::mouseReleaseEvent(QMouseEvent *)
{
    emit labelIdChange(id);
}

void chatLabelTag::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton){
        QPoint globalPos = mapToGlobal(e->pos());
        m->exec(globalPos);
    }
}
