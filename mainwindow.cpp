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
    QTime t=QTime::currentTime();
    int hour  = t.hour();
    if(hour>=8&&hour<=18){
        p.drawPixmap(this->rect(),QPixmap(":/new/prefix1/E:/sunormoon/sun.gif").scaled(this->size()));
    }else
    p.drawPixmap(this->rect(),QPixmap(":/new/prefix1/E:/sunormoon/moon.gif").scaled(this->size()));

}

