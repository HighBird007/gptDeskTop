#include "chatlabeltag.h"

chatLabelTag::chatLabelTag(int a,QString c) {
    id =a;
    content = c;
    this->setText(content);
    this->setFixedSize(QSize(150,100));
    this->setStyleSheet("border: 1px solid black; margin: 5px; padding: 5px;");
}

void chatLabelTag::mouseReleaseEvent(QMouseEvent *)
{
    emit labelIdChange(id);

}
