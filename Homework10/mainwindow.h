#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    QTimer *timer_cycle;

    bool show_info = false;

    QString text_info;

    int coord_info_x;
    int coord_info_y;

    double scale_scene;

    double x_axis = 1; //вращение мира по оси X
    double y_axis = 1; //вращение мира по оси Y

    //размерспутникапланеты
    int moon_size = 50;
    //размерорбитыспутника
    int orbital_moon_size = 220;
    //орбитальнаяскоростьспутника
    double orbital_moon_speed = 2.6;
    //размер звезды
    int star_size = 200;
    //скорость вращения спутника
    double speed_moon_rotation = 2.5;
    // скорость вращения звезды
    double speed_star_rotation = 2.5;
    //счетчик вращения орбиты спутника
    double orbital_moon_rotation = 0;

    //счетчиквращенияспутника
    double moon_rotation;
    //счетчиквращениязвезды
    double star_rotation;
    //размерорбиты
    int orbital_size;
    //орбитальнаяскорость
    double orbital_speed;
    //счетчиквращенияорбиты
    double orbital_rotation=0;
    //размерпланеты
    int planet_size;
    //насколькоувеличиваетсяшапкаатмосферы
    int atmosphere_up_size;
    //скоростьвращенияпланеты
    double speed_planet_rotation;
    //счетчиквращенияпланеты
    double planet_rotation=0;
    //скоростьвращенияатмосферы
    double speed_atmosphere_rotation;
    //счетчиквращенияатмосферы
    double atmosphere_rotation=0;

    //звездный фон
    QImage star_background;
    //текстурная карта планеты
    QImage planet_texture;
    //маска альфа-смешивания планеты
    QImage planet_alpha;
    //итоговый объект планеты
    QImage planet;
    //тень планеты
    QImage planet_shadow;
    //текстурная карта спутника планеты
    QImage moon_texture;
    //маска альфа-смешивания спутника
    QImage moon_alpha;
    //итоговый объект спутника
    QImage moon;
    //тень спутника
    QImage moon_shadow;
    //текстурная карта звезды
    QImage star_texture;
    //маска альфа-смешивания звезды
    QImage star_alpha;
    //итоговый объект звезды
    QImage star;
    //текстурная карта ночных огней городов
    QImage planet_lights_texture;
    //маска альфа-смешивания ночных огней городов
    QImage planet_lights_alpha;
    //итоговый объект ночных огней городов
    QImage planet_lights;
    //текстурная карта атмосферы
    QImage planet_atmosphere_texture;
    //маска альфа-смешивания атмосферы
    QImage planet_atmosphere_alpha;
    //итоговый объект атмосферы
    QImage planet_atmosphere;

    ~MainWindow();

protected:

    void keyPressEvent(QKeyEvent *event);

    bool eventFilter(QObject *target, QEvent *event);

private:
    Ui::MainWindow *ui;

private slots:

    void paintEvent(QPaintEvent *event);

    void cycle();

};

#endif // MAINWINDOW_H
