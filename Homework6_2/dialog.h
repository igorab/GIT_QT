#ifndef DIALOG_H
#define DIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include "mainwindow.h"


// возьмем какое-нибудь число отсюда .....

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog();

protected:

    void closeEvent(QCloseEvent *);


private:

    Ui::Dialog *ui;

    MainWindow *mainwindow;

    QString data;

signals:
    void sendData(QString, double);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();



};

#endif // DIALOG_H
