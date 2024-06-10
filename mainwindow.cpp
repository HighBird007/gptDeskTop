#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start_connect();
    this->setFixedSize(this->size());
    ui->comboBox->setEditable(true);
    this->setWindowTitle("登录");
    this->setWindowFlags( Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->label_3->setFixedSize(this->size());
    QTime t=QTime::currentTime();
    int hour  = t.hour();
    qDebug()<<hour;
    QMovie *m;
    if(hour>=8&&hour<=18){
        m=new QMovie(":/new/prefix1/G:/nature-4119.gif");
    }else{
        m=new QMovie(":/new/prefix1/G:/moon-594.gif");
    }
    m->setScaledSize(ui->label_3->size());
    ui->label_3->setMovie(m);
    m->start();
    qDebug()<<this->size();
    qDebug()<<ui->label_3->size();
this->setWindowIcon(QIcon(QPixmap(":/new/prefix1/G:/openai-black.png")));
    connect(ui->loginbutton,&QPushButton::clicked,this,&MainWindow::loginbuttonclick);
    connect(&connecttoserve::getinstance(),&connecttoserve::loginjugder,this,[=](bool b){
        if(b){
            sql.insertnewuser(a,p);
            chatmain *cm=new chatmain();
            cm->show();
            this->hide();
        }else {
            QMessageBox::warning(this,"错误","账号或者密码不对");
        }
    });
    vec = sql.getlastlogin();
    for(int i = 0;i<vec.size();i++){
        ui->comboBox->addItem(vec[i].first);
        passwordset.push_back(vec[i].second);
    }
    if(!vec.empty())ui->lineEdit->setText(passwordset[0]);
    connect(ui->comboBox,&QComboBox::currentIndexChanged,this,[=](int a){
        ui->lineEdit->setText(passwordset[a]);
    });
    connect(&udpsocketmodel::getinstance(),&udpsocketmodel::udpnotice,this,[=](QString a){
        QMessageBox::warning(this,"更新提醒",a);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginbuttonclick()
{
    a=ui->comboBox->currentText();
    p=ui->lineEdit->text();
    user_login(a,p);
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);


}

