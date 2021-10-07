#ifndef CIRCLES_H
#define CIRCLES_H

#include <QMainWindow>
#include <QPainter>


QT_BEGIN_NAMESPACE
namespace Ui { class Circles; }
QT_END_NAMESPACE

class Circles : public QMainWindow
{
    Q_OBJECT

public:
    Circles(QWidget *parent = nullptr);
    ~Circles();

private:
    Ui::Circles *ui;

    QTimer *timer;

    qreal alpha = 0;

private slots:
    void paintEvent(QPaintEvent *event);
    void refresh();

};
#endif // CIRCLES_H
