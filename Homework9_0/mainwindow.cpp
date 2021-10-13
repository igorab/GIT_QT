#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QImage"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    speed_planet_rotation = 2.5;
    speed_atmosphere_rotation = 2.9;

    planet_size = 500;
    atmosphere_up_size = 6;

    ui->setupUi(this);

    star_background.load("img/star_background.jpg");
    planet_texture.load("img/planet_texture.png");
    planet_alpha.load("img/planet_alpha.png");
    planet_shadow.load("img/planet_shadow.png");
    planet_lights_texture.load("img/planet_lights_texture.png");
    planet_lights_alpha.load("img/planet_lights_alpha.png");

    planet_atmosphere_texture.load("img/planet_atmosphere_texture.png");
    planet_atmosphere_alpha.load("img/planet_atmosphere_alpha.png");


    planet_alpha = planet_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_shadow = planet_shadow.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_lights_texture = planet_lights_texture.scaled(planet_texture.width(), planet_texture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_lights_alpha = planet_lights_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    planet_atmosphere_texture = planet_atmosphere_texture.scaled(planet_texture.width(), planet_texture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_atmosphere_alpha = planet_atmosphere_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

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
    painter.drawImage(-(planet_size + atmosphere_up_size)/2, -(planet_size + atmosphere_up_size)/2, planet_atmosphere);
    painter.drawImage(-planet_size/2, -planet_size/2, planet_shadow);
    painter.drawImage(-planet_size/2, -planet_size/2, planet_lights);

    painter.restore();

}

void MainWindow::cycle()
{
    planet = planet_texture.copy(planet_rotation, 0, planet_texture.height(), planet_texture.height());
    planet = planet.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    planet_lights = planet_lights_texture.copy(planet_rotation, 0, planet_lights_texture.height(), planet_lights_texture.height());
    planet_lights = planet_lights.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    planet_atmosphere = planet_atmosphere_texture.copy(atmosphere_rotation, 0, planet_atmosphere_texture.height(), planet_atmosphere_texture.height());
    planet_atmosphere = planet_atmosphere.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    QPainter painter(&planet);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.drawImage(0, 0, planet_alpha);

    QPainter painter2(&planet_lights);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter2.drawImage(0, 0, planet_lights_alpha);

    QPainter painter3(&planet_atmosphere);
    painter3.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter3.drawImage(0, 0, planet_atmosphere_alpha);


    planet_rotation += speed_planet_rotation;

    if (planet_rotation + planet_texture.height() >= planet_texture.width())
        planet_rotation = 0;

    atmosphere_rotation += speed_atmosphere_rotation;

    if (atmosphere_rotation + planet_atmosphere_texture.height() >= planet_atmosphere_texture.width())
        atmosphere_rotation = 0;

    update();
}

