#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QTimer>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    QTimer *timer_cycle;

    int planet_size;

    int atmosphere_up_size;

    double speed_planet_rotation;

    double planet_rotation = 0;

    double atmosphere_rotation = 0;

    double speed_atmosphere_rotation;

    QImage star_background;

    QImage planet_texture;

    QImage planet_alpha;

    QImage planet;

    QImage planet_shadow;

    QImage planet_lights_texture;

    QImage planet_lights_alpha;

    QImage planet_lights;

    QImage planet_atmosphere_texture;

    QImage planet_atmosphere_alpha;

    QImage planet_atmosphere;




private:

    Ui::MainWindow *ui;

private slots:

    void paintEvent(QPaintEvent *event);
    void cycle();

};

#endif // MAINWINDOW_H
