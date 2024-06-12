#include "chatmain.h"
#include "ui_chatmain.h"

chatmain::chatmain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatmain)
{
    ui->setupUi(this);
    ui->scrollArea->setStyleSheet("QScrollArea { background: transparent; }"
                              "QScrollArea > QWidget > QWidget { background: transparent; }"
                              "QScrollBar:vertical { background: #2D2D30; }"
                              "QScrollBar:horizontal { background: #2D2D30; }");
    cl = new chatLabelsShow(this);
    cl->setFixedSize(200,this->height());
    init();
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::rangeChanged,this,[=](int a,int b){
        Q_UNUSED(a);
        ui->scrollArea->verticalScrollBar()->setValue(b);
    });

}

chatmain::~chatmain()
{
    delete ui;
}
//发送信息
void chatmain::on_pushButton_clicked()
{
    if(currentchatid==-1){
        return ;
    }
    QString content=ui->textEdit_2->toPlainText();
    chatsqlmodel.insertchat(content,0);
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = content;
    QJsonArray messagesArray = panelmap[currentchatid]->gethistorymess();
    messagesArray.append(messageObject);
    QJsonObject requestBody ;
    requestBody["model"] = userchose;
    requestBody["messages"] = messagesArray;
    requestBody["stream"]=true;
    QJsonObject obj;
    obj["type"]="chat";
    obj["chatId"]=currentchatid;
    obj["data"]=requestBody;
    QJsonDocument jsonDoc(obj);
    panelmap[currentchatid]->adduserbox(content);
    connecttoserve::getinstance().sendtoserve(jsonDoc);
    ui->textEdit_2->clear();
}

void chatmain::receivehistory(QJsonObject data)
{
           QJsonArray arr = data["content"].toArray();
           int midid = data["chatId"].toInt();
           for(int i = 0 ;i<arr.size();i++){
           QJsonObject o =arr[i].toObject();
           chatbox * box =new chatbox(o["chat"].toString(),o["peoormac"].toInt());
           panelmap[midid]->addhisbox(box);
        }
}

void chatmain::init()
{
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle("聊天界面");
    this->setWindowIcon(QIcon(QPixmap(":/new/prefix1/G:/openai-black.png")));
    //解析gpt的聊天
      connect(&connecttoserve::getinstance(),&connecttoserve::history,this,&chatmain::receivehistory);
    connect(&connecttoserve::getinstance(), &connecttoserve::getdata, this, [=](QJsonObject o) {
        QJsonArray choicesArray = o["choices"].toArray();
        QString chatmidid = o["id"].toString();
        if (!choicesArray.isEmpty()) {
            QJsonObject choiceObject = choicesArray[0].toObject();
            QJsonObject messageObject = choiceObject["delta"].toObject();
            QString chatContent = messageObject["content"].toString();
            panelmap[currentchatid]->addnewbox(chatmidid,1,chatContent);
        }
    });
      //将获取的聊天标签存进map 设置对应的聊天窗口为nullptr
     connect(&connecttoserve::getinstance(),&connecttoserve::chatLabelsdata,this,[=](QJsonObject o){
        std::vector<int> vec =cl->initshow(o);
        for(int i= 0 ;i<(int)vec.size();i++){
            int mid = vec[i];
            if(panelmap.find(mid)==panelmap.end()){
                panelmap[mid] = nullptr;
            }
        }
    });
    //设置聊天背景
     QLabel *l =new QLabel(this);
     l->setFixedSize(this->size());
     l->lower();
     QMovie *m;
     int  hour = QTime::currentTime().hour();
     if(hour>=8&&hour<=18){
         m=new QMovie(":/new/prefix1/G:/nature-4119.gif");
     }else{
         m=new QMovie(":/new/prefix1/G:/moon-594.gif");
     }
     m->setScaledSize(l->size());
     l->setMovie(m);
     m->start();
    //初始化模型选择combox
    strlist<<"gpt-4o"<<"gpt-3.5-turbo";
    ui->comboBox->addItems(strlist);
    userchose = ui->comboBox->currentText();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,[&](QString a){
        userchose = a;
    });
    //获得聊天标签
    connecttoserve::getinstance().getLabels();
    connect(cl,&chatLabelsShow::labelId,this,&chatmain::userChangeChat);
}
void chatmain::userChangeChat(int id)
{
    currentchatid = id;
    if(panelmap[id]==nullptr){
        chatshowwidget *c =new chatshowwidget;
        panelmap[id]=c;
        connecttoserve::getinstance().gethistory(id);
    }
    chatshowwidget *c =(chatshowwidget*)ui->scrollArea->takeWidget();
    panelmap[c->getchatid()] = c;
    ui->scrollArea->setWidget(panelmap[id]);
}
void chatmain::on_pushButton_2_clicked()
{
    if(cl->isVisible())
    cl->hide();
    else
    cl->show();
}

