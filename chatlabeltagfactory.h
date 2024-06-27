#ifndef CHATLABELTAGFACTORY_H
#define CHATLABELTAGFACTORY_H

#include <QObject>
#include <chatlabeltag.h>
class chatLabelTagFactory
{
    Q_OBJECT
public:
    chatLabelTagFactory();
    chatLabelTag* createTag(int id,QString c);
};

#endif // CHATLABELTAGFACTORY_H
