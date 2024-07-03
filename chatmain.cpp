#include "chatmain.h"
#include "ui_chatmain.h"

chatmain::chatmain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatmain)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    ui->pushButton->setFixedSize(100,20);
    ui->comboBox->setFixedSize(100,20);
    ui->textEdit_2->setFixedSize(1000,100);
    ui->widget_2->setFixedSize(200,this->height()-20);
    ui->scrollArea->setStyleSheet("QScrollArea { background: transparent; }"
                              "QScrollArea > QWidget > QWidget { background: transparent; }"
                              "QScrollBar:vertical { background: #2D2D30; }"
                              "QScrollBar:horizontal { background: #2D2D30; }");
    init();
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::rangeChanged,this,[=](int a,int b){
        Q_UNUSED(a);
        ui->scrollArea->verticalScrollBar()->setValue(b);
    });
    connecttoserve::getinstance().getLabels();
    ui->textEdit_2->hide();
    ui->textEdit_2->setStyleSheet(
        "QTextEdit#textEdit_2 {"
        "    background-color: rgba(255, 255, 255, 150);"  // 半透明白色背景
        "    border: 1px solid gray;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    color: black;"  // 设置文本颜色为黑色
        "    font-size: 14px;"  // 设置字体大小
        "}"
        );
    ui->comboBox->hide();
    ui->pushButton->hide();
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
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = content;
    QJsonObject obj;
    QJsonObject requestBody ;
    requestBody["model"] = userchose;
    QJsonArray messagesArray;
    if(userchose=="claude-3-5-sonnet-20240620"){
        messagesArray.append(messageObject);
    }
    else {
         messagesArray = panelmap[currentchatid]->gethistorymess();
        messagesArray.append(messageObject);
    }
    requestBody["messages"] = messagesArray;
      requestBody["stream"]=true;
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
    this->setWindowTitle("ChatGpt");
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
        std::vector<int> vec =ui->widget_2->initshow(o);
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
     strlist<<"gpt-4o"<<"gpt-3.5-turbo"<<"claude-3-5-sonnet-20240620";
    ui->comboBox->addItems(strlist);
    userchose = ui->comboBox->currentText();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,[&](QString a){
        userchose = a;
    });
    //获得聊天标签
    connect(ui->widget_2,&chatLabelsShow::labelId,this,&chatmain::userChangeChat);
    connect(ui->widget_2,&chatLabelsShow::deleteLabelId,this,&chatmain::userDeleteTag);
}
void chatmain::userChangeChat(int id)
{

    currentchatid = id;
    if(panelmap[id]==nullptr){
        chatshowwidget *c =new chatshowwidget(this);
        panelmap[id]=c;
        connecttoserve::getinstance().gethistory(id);
    }
    ui->scrollArea->takeWidget();
    ui->scrollArea->setWidget(panelmap[id]);

    ui->textEdit_2->show();
    ui->comboBox->show();
    ui->pushButton->show();
    ui->pushButton->setEnabled(true);
}

void chatmain::userDeleteTag(int id)
{
    auto it = panelmap.find(id);
    if(it == panelmap.end())
        return;

    QWidget* pageWidget = it->second;
    if(pageWidget) {
        pageWidget->setParent(nullptr);
        pageWidget->deleteLater();
    }

    panelmap.erase(it);
    currentchatid = -1;
    ui->pushButton->setEnabled(false);

    // 可能需要更新滚动区域或其他UI元素
    ui->scrollAreaWidgetContents->update();
}


void chatmain::on_pushButton_2_clicked()
{
    userChart * c = new userChart;
    c->show();
}

