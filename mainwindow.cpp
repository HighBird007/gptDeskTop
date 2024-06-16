#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start_connect();
    this->setFixedSize(this->size());
    this->setWindowTitle("登录");
    this->setWindowFlags( Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowIcon(QIcon(QPixmap(":/new/prefix1/G:/openai-black.png")));
    initBackGround();
    connect(ui->loginbutton,&QPushButton::clicked,this,&MainWindow::loginbuttonclick);
    connect(&connecttoserve::getinstance(),&connecttoserve::loginjugder,this,&MainWindow::loginJudge);
    initAcountAndPassword();
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

void MainWindow::initBackGround()
{
    l= new QLabel(this);
    int h = QTime::currentTime().hour();
    QString imagePath;
    if (h >= 5 && h < 7) {
        // Dawn
        imagePath = ":/new/prefix1/G:/sre/1.jpeg";
    } else if (h >= 7 && h < 11) {
        // Morning
        imagePath = ":/new/prefix1/G:/sre/2.jpeg";
    } else if (h >= 11 && h < 13) {
        // Noon
        imagePath = ":/new/prefix1/G:/sre/3.jpeg";
    } else if (h >= 13 && h < 16) {
        // Afternoon
        imagePath = ":/new/prefix1/G:/sre/4.jpeg";
    } else if (h >= 16 && h < 19) {
        // Evening
        imagePath = ":/new/prefix1/G:/sre/5.jpeg";
    } else if (h >= 19 && h < 20) {
        // Dusk
        imagePath = ":/new/prefix1/G:/sre/6.jpeg";
    } else if (h >= 20 && h < 24) {
        // Night
        imagePath = ":/new/prefix1/G:/sre/7.jpeg";
    } else if (h >= 0 && h < 3) {
        // Midnight
        imagePath = ":/new/prefix1/G:/sre/8.jpeg";
    } else if (h >= 3 && h < 5) {
        // Late Night
        imagePath = ":/new/prefix1/G:/sre/9.jpeg";
    } else {
        // Default case to avoid empty imagePath
        imagePath = ":/new/prefix1/G:/sre/default.jpeg";
    }

    l->setPixmap(QPixmap(imagePath).scaled(this->size()));

    l->setFixedSize(this->size());
    l->lower();
    l->show();
}

void MainWindow::loginJudge(bool b)
{
    if(b){
        sql.insertnewuser(a,p);
        chatmain *cm=new chatmain();
        cm->show();
        this->hide();
    }else {
        QMessageBox::warning(this,"错误","账号或者密码不对");
    }
}

void MainWindow::initAcountAndPassword()
{
    ui->comboBox->setEditable(true);
    vec = sql.getlastlogin();
    for(int i = 0;i<vec.size();i++){
        ui->comboBox->addItem(vec[i].first);
        passwordset.push_back(vec[i].second);
    }
    if(!vec.empty())ui->lineEdit->setText(passwordset[0]);

    connect(ui->comboBox,&QComboBox::currentIndexChanged,this,[=](int a){
        ui->lineEdit->setText(passwordset[a]);
    });
}



