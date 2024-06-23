#include "chatlabelsshow.h"
#include "ui_chatlabelsshow.h"

chatLabelsShow::chatLabelsShow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatLabelsShow)
{
    ui->setupUi(this);
    l=new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(l);
    space =new QSpacerItem(200,200,QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(ui->createNewTag,&QPushButton::clicked,this,&chatLabelsShow::createtag);
}

chatLabelsShow::~chatLabelsShow()
{
    delete ui;
}

std::vector<int> chatLabelsShow::initshow(QJsonObject data)
{
    std::vector<int> vec;
    qDebug()<<data;
    QJsonArray arr = data["content"].toArray();
    for(int i = 0 ;i<arr.size();i++){
        QJsonObject d = arr[i].toObject();
        if(uset.find(d["chatLabelId"].toInt())!=uset.end()){
            continue;
        }
        uset.insert(d["chatLabelId"].toInt());
        chatLabelTag *tag = new chatLabelTag(d["chatLabelId"].toInt(),d["chatLabelContent"].toString());
        connect(tag,&chatLabelTag::labelIdChange,this,[=](int id){
            emit labelId(id);
        });
        l->addWidget(tag);
        vec.push_back(d["chatLabelId"].toInt());
    }
    l->addSpacerItem(space);
    return vec;
}

void chatLabelsShow::createtag()
{
    connecttoserve::getinstance().createNewTag();
}
