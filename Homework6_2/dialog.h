#ifndef DIALOG_H
#define DIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    MainWindow mw;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
