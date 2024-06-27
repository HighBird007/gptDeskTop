#include "chatlabeltagfactory.h"

chatLabelTagFactory::chatLabelTagFactory() {}

chatLabelTag *chatLabelTagFactory::createTag(int id, QString c)
{
    chatLabelTag *tag = new chatLabelTag(id,c);

}
