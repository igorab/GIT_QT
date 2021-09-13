#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{    
    button->animateClick(3000);
}


void Dialog::on_buttonBox_rejected()
{
    int i = 0;
    i --;
    -- i;

    char j = 2;
    j = j >> 1;
    j = j >> 1;

    char a = 1;
    a = j;
    a ++;
}


void Dialog::on_buttonBox_accepted()
{
    // open form
    mw.show();
    mw.setParams("aaaaaa");

    this->hide();
}

