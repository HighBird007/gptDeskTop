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
    QJsonObject obj;
    obj["type"]="chat";
    obj["data"]=requestBody;
    QJsonDocument jsonDoc(obj);
    chatbox *box =new chatbox(content,0,this);
     panelmap[currentchatid]->addnewbox(box);
    connecttoserve::getinstance().sendtoserve(jsonDoc);
    ui->textEdit_2->clear();
}

void chatmain::receivehistory(QJsonObject data)
{
    QJsonArray arr = data["content"].toArray();
             for(int i = 0 ;i<arr.size();i++){
           QJsonObject o =arr[i].toObject();
           chatbox * box =new chatbox(o["chat"].toString(),o["peoormac"].toInt());
           panelmap[currentchatid]->addnewbox(0,box);
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
        // 获取choices数组
        QJsonArray choicesArray = o["choices"].toArray();
        // 获取第一个选择项
        if (!choicesArray.isEmpty()) {
            QJsonObject choiceObject = choicesArray[0].toObject();
            // 获取message对象
            QJsonObject messageObject = choiceObject["message"].toObject();
            // 获取content字段中的聊天内容
            QString chatContent = messageObject["content"].toString();
            //1是机器人
            chatbox *box =new chatbox(chatContent,1,this);
            chatsqlmodel.insertchat(chatContent,1);
            panelmap[currentchatid]->addnewbox(box);
        }
    });
    //设置聊天背景
    QLabel *l =new QLabel(this);
    l->setFixedSize(this->size());
    l->lower();
    QMovie *m;
    QTime t;
    int  hour = t.hour();
    if(hour>=8&&hour<=18){
        m=new QMovie(":/new/prefix1/G:/nature-4119.gif");
    }else{
        m=new QMovie(":/new/prefix1/G:/moon-594.gif");
    }
    m->setScaledSize(l->size());
    l->setMovie(m);
    //初始化模型选择combox
    strlist<<"gpt-4o"<<"gpt-3.5-turbo"<<"gpt-4-turbo";
    ui->comboBox->addItems(strlist);
    userchose = ui->comboBox->currentText();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,[&](QString a){
        userchose = a;
    });
    m->start();
    //得到历史聊天记录
    connecttoserve::getinstance().gethistory();

}


