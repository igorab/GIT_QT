#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QImage"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    speed_planet_rotation = 2.5;

    planet_size = 500;

    ui->setupUi(this);

    star_background.load("img/star_background.jpg");

    planet_texture.load("img/planet_texture.png");

    planet_alpha.load("img/planet_alpha.png");

    planet_alpha = planet_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    timer_cycle = new QTimer();

    connect(timer_cycle, SIGNAL(timeout()), this, SLOT(cycle()));

    timer_cycle->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(), ui->screen->geometry().width(), ui->screen->geometry().height());

    star_background = star_background.scaled(ui->screen->geometry().width(), ui->screen->geometry().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter.drawImage(0, 0, star_background);
    painter.save();

    painter.translate(ui->screen->geometry().width()/2, ui->screen->geometry().height()/2);

    painter.drawImage(-planet_size/2, -planet_size/2, planet);

}

void MainWindow::cycle()
{
    planet = planet_texture.copy(planet_rotation, 0, planet_texture.height(), planet_texture.height());

    planet = planet.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );


    QPainter painter(&planet);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.drawImage(0, 0, planet_alpha );


    planet_rotation += speed_planet_rotation;

    if (planet_rotation + planet_texture.height() >= planet_texture.width())
        planet_rotation = 0;

    update();
}

