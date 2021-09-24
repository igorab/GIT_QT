#include "circles.h"
#include "ui_circles.h"
#include <QTimer>

Circles::Circles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Circles)
{
    ui->setupUi(this);

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this,  SLOT(refresh));

    timer->start(100);
}

Circles::~Circles()
{
    delete ui;
}

void Circles::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    QVector<qreal> dashes;
    qreal space = 4;
    dashes << 1 << space << 3 << space << 9 << space << 27 << space << 9 << space;
    pen.setDashPattern(dashes);

    pen.setWidth(5);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    brush.setColor(Qt::blue);
    brush.setStyle(Qt::Dense5Pattern);

    painter.setBrush(brush);
    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(), ui->screen->geometry().width(), ui->screen->geometry().height());

    painter.drawLine(50,50,500,500);
    painter.drawRect(300,20, 100, 50);

    painter.drawRect(x,y, 200, 200);
}

void Circles::refresh()
{
    if (x >= ui->screen->geometry().width()) dirx = -1;
    else dirx    = 1;

    if (y>=ui->screen->geometry().height()) diry = -1;
    else diry = 1;

    x = x + dirx;
    y = y + diry;
    x = x+1;

    update();

}

