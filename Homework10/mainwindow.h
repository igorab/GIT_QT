#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

protected:

    void mousePressEvent(QMouseEvent *event);

    bool eventFilter(QObject*target, QEvent*event);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
