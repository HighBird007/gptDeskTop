#include "chatlabel.h"
#include "ui_chatlabel.h"

chatLabel::chatLabel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chatLabel)
{
    ui->setupUi(this);
}

chatLabel::~chatLabel()
{
    delete ui;
}
