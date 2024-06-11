#include "chatmain.h"
#include "ui_chatmain.h"

chatmain::chatmain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatmain)
{
    ui->setupUi(this);
    chatshowwidget *showwidget = new chatshowwidget;
    ui->scrollArea->setWidget(showwidget);
    panelmap.insert(std::make_pair(currentchatid,showwidget));
    ui->scrollArea->setStyleSheet("QScrollArea { background: transparent; }"
                              "QScrollArea > QWidget > QWidget { background: transparent; }"
                              "QScrollBar:vertical { background: #2D2D30; }"
                              "QScrollBar:horizontal { background: #2D2D30; }");
    init();
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::rangeChanged,this,[=](int a,int b){

        ui->scrollArea->verticalScrollBar()->setValue(b);
    });
}

chatmain::~chatmain()
{
    delete ui;
}

void chatmain::on_pushButton_clicked()
{
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
    obj["data"]=requestBody;
    QJsonDocument jsonDoc(obj);
    panelmap[currentchatid]->adduserbox(content);
    connecttoserve::getinstance().sendtoserve(jsonDoc);
    ui->textEdit_2->clear();
}

void chatmain::receivehistory(QJsonObject data)
{
             QJsonArray arr = data["content"].toArray();
             for(int i = 0 ;i<arr.size();i++){
           QJsonObject o =arr[i].toObject();
           chatbox * box =new chatbox(o["chat"].toString(),o["peoormac"].toInt());
           panelmap[currentchatid]->addhisbox(box);
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
            //1是机器人
          //  chatsqlmodel.insertchat(chatContent,1);
            panelmap[currentchatid]->addnewbox(chatmidid,1,chatContent);
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
    strlist<<"gpt-4o"<<"gpt-3.5-turbo"<<"gpt-4-turbo";
    ui->comboBox->addItems(strlist);
    userchose = ui->comboBox->currentText();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,[&](QString a){
        userchose = a;
    });
    //得到历史聊天记录
    connecttoserve::getinstance().gethistory();
}


