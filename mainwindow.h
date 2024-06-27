#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <connecttoserve.h>
#include <QTimer>
#include <chatmain.h>
#include <loginsqlmodel.h>
#include <QMessageBox>
#include <QPainter>
#include <QMovie>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loginbuttonclick();

private:
    Ui::MainWindow *ui;
    bool loginjudger=false;
    QString a;
    QString p;
    QVector<std::pair<QString,QString>> vec;
    loginsqlmodel sql;
    QVector<QString> passwordset;
    QLabel *l;
private:;
    void initBackGround();
    void loginJudge(bool);
    void initAcountAndPassword();
};
#endif // MAINWINDOW_H
