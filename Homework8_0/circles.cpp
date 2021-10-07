#include "circles.h"
#include "ui_circles.h"
#include <QTimer>

Circles::Circles(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Circles)
{
    ui->setupUi(this);

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this,  SLOT(refresh()));

    timer->start(100);
}

Circles::~Circles()
{
    delete ui;
}

void Circles::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPoint *CenterStar = new QPoint(300, 300);

    painter.translate(*CenterStar);

    QPen   PenStar;

    QVector<qreal> dashes;
    qreal space = 4;
    dashes << 1 << space << 3 << space << 9 << space << 27 << space << 9 << space;
    PenStar.setDashPattern(dashes);
    PenStar.setWidth(5);
    PenStar.setColor(Qt::red);
    painter.setPen(PenStar);

    QBrush BrushStar;
    BrushStar.setColor(Qt::blue);
    BrushStar.setStyle(Qt::Dense5Pattern);

    painter.setBrush(BrushStar);
    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(), ui->screen->geometry().width(), ui->screen->geometry().height());

    int starRadius = 100;

    // draw Star
    painter.drawEllipse(QPoint(0,0), starRadius, starRadius);

    painter.save();

    // draw Planet
    QColor PlanetColor(0, 255, 255);
    QBrush BrushPlanet(PlanetColor, Qt::SolidPattern);
    QPen PenPlanet( BrushPlanet, 5);

    painter.rotate(alpha);
    painter.translate(2*starRadius, 0);

    QPoint CenterPlanet(0, 0);

    BrushPlanet.setColor(Qt::yellow);
    painter.setBrush(BrushPlanet);
    painter.setPen(PenPlanet);
    painter.drawEllipse(CenterPlanet, 50, 30);

    painter.restore();

}

void Circles::refresh()
{       
    alpha --;

    if (alpha == -360) alpha = 0;

    update();
}

