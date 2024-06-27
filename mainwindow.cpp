#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start_connect();
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



void MainWindow::initBackGround()
{
    // 设置QComboBox的固定大小和字体
    ui->comboBox->setFixedSize(287, 35);
    ui->comboBox->setStyleSheet(
        "QComboBox#comboBox {"
        "    background-color: rgba(255, 255, 255, 150);"  // 半透明白色背景
        "    border: 1px solid gray;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 15px;"
        "    border-left-width: 1px;"
        "    border-left-color: darkgray;"
        "    border-left-style: solid;"
        "    border-top-right-radius: 3px;"
        "    border-bottom-right-radius: 3px;"
        "}"
        "QComboBox::down-arrow {"
        "    image: url(:/new/prefix1/G:/kk.png);"  // 你可以使用自定义箭头图片
        "    width: 10px;"  // 调整图片的宽度
        "    height: 10px;"  // 调整图片的高度
        "    padding: 2px;"  // 调整图片的填充
        "}"
        );

    QFont comboBoxFont;
    comboBoxFont.setFamily("Arial");   // 字体名称，例如 "Arial"
    comboBoxFont.setPointSize(14);     // 字体大小
    comboBoxFont.setItalic(false);     // 斜体
    ui->comboBox->setFont(comboBoxFont);
    ui->loginbutton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(128, 128, 128, 128);"  // 半透明背景颜色 (灰色，50% 透明度)
        "   color: white;"                               // 文字颜色
        "   border: 2px solid #ffffff;"                  // 边框颜色和宽度
        "   border-radius: 10px;"                        // 边框圆角
        "   font-size: 14px;"                            // 字体大小
        "   padding: 5px 10px;"                          // 内边距
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient("
        "       spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "       stop:0 rgba(255, 0, 0, 128), "           // 渐变起点颜色 (红色，50% 透明度)
        "       stop:1 rgba(0, 0, 255, 128)"             // 渐变终点颜色 (蓝色，50% 透明度)
        "   );"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(0, 0, 0, 150);"       // 按下时的背景颜色 (黑色，40% 透明度)
        "}"
        );

    // 设置QLineEdit的固定大小和字体
    ui->lineEdit->setFixedSize(287, 35);
    ui->lineEdit->setStyleSheet(
        "QLineEdit {"
        "    background-color: rgba(255, 255, 255, 150);"  // 半透明白色背景
        "    border: 1px solid gray;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}"
        "QLineEdit::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 15px;"
        "    border-left-width: 1px;"
        "    border-left-color: darkgray;"
        "    border-left-style: solid;"
        "    border-top-right-radius: 3px;"
        "    border-bottom-right-radius: 3px;"
        "}"
        );
    QFont lineEditFont;
    lineEditFont.setFamily("Arial");   // 字体名称，例如 "Arial"
    lineEditFont.setPointSize(12);     // 字体大小
    lineEditFont.setItalic(false);     // 斜体
    ui->lineEdit->setFont(lineEditFont);
    this->setFixedSize(420,300);
    this->setWindowTitle("登录");
    this->setWindowFlags( Qt::WindowCloseButtonHint);
    this->setWindowIcon(QIcon(QPixmap(":/new/prefix1/G:/openai-black.png")));
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

    // QString buttonStyle = R"(
    //     QPushButton {
    //         color: white;               /* 白色文字 */
    //         text-align: center;         /* 文字居中 */
    //         text-decoration: none;      /* 无下划线 */
    //         display: inline-block;      /* 行内块 */
    //         margin: 4px 2px;            /* 外边距 */
    //         border-radius: 8px;         /* 边角弧度 */
    //     }

    //     QPushButton:hover {
    //         background-color: #45a049;
    //     }

    //     QPushButton:pressed {
    //         background-color: #3e8e41;
    //     }
    // )";
    // ui->loginbutton->setStyleSheet(buttonStyle);
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



