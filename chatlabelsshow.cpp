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
    connect(ui->createNewTag,&QPushButton::clicked,this,&chatLabelsShow::createNewLabel);
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: 2px solid #c3c3c3;"
        "    border-radius: 5px;"
        "    background-color: #f0f0f0;"
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #e1e1e1;"
        "    width: 12px;"
        "    margin: 15px 0 15px 0;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #a9a9a9;"
        "    min-height: 20px;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical {"
        "    border: none;"
        "    background: none;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "    border: none;"
        "    background: none;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}"
        );
    ui->createNewTag->setStyleSheet(
        "QPushButton {"
        "    background-color: #5cb85c;"
        "    border: 1px solid #4cae4c;"
        "    border-radius: 5px;"
        "    color: #fff;"
        "    padding: 5px 10px;"
        "    font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4cae4c;"
        "    border-color: #398439;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #398439;"
        "    border-color: #2d6b2d;"
        "}"
        );
}

chatLabelsShow::~chatLabelsShow()
{
    delete ui;
}

std::vector<int> chatLabelsShow::initshow(QJsonObject data)
{
    std::vector<int> vec;
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
        connect(tag,&chatLabelTag::deleteSelf,this,[=](int id){
            l->removeWidget(tag);
            connecttoserve::getinstance().deleteTag(id);
            tag->deleteLater(); // 删除widget并释放内存
            uset.erase(id);
        });
        l->addWidget(tag);
        vec.push_back(d["chatLabelId"].toInt());
        if(i==0){
            maxid = d["chatLabelId"].toInt();
        }
    }
    l->addSpacerItem(space);
    return vec;
}



void chatLabelsShow::createNewLabel()
{
    connecttoserve::getinstance().createNewTag();
    maxid++;
    chatLabelTag *t = new chatLabelTag(maxid,QTime::currentTime().toString());
    connect(t,&chatLabelTag::labelIdChange,this,[=](int id){
        emit labelId(id);
    });

    l->insertWidget(0,t);
    uset.insert(maxid);
    emit labelId(maxid);
}
