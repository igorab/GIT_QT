#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //необходимо назначить фильтр для центрального виджета, в котором реализуем обработчик событий мыши

    // становим фильтр событий на центральный виджет
    ui->centralwidget->installEventFilter(this);

    // становим отслеживание движений мыши
    ui->centralwidget->setMouseTracking(true);

    x_axis = 0;
    y_axis = 0;
    scale_scene = 1;
    orbital_size = 280;
    orbital_speed = 0.2;
    speed_planet_rotation = 2.5;
    speed_atmosphere_rotation = 2.9;
    planet_size = 150;
    atmosphere_up_size = 6;
    moon_size=50;
    orbital_moon_size=120;//размерорбитыспутника
    orbital_moon_speed=1.6;//орбитальнаяскоростьспутника
    star_size=200;//размерзвезды
    speed_moon_rotation=2.5;//скоростьвращенияспутника
    speed_star_rotation=2.5;//скоростьвращениязвезды

    //загрузказвездногофона
    star_background.load("img/star_background.jpg");
    //загрузкатекстурнойкартыпланеты
    planet_texture.load("img/planet_texture.png");
    //загрузкамаскиальфа-смешиванияпланеты
    planet_alpha.load("img/planet_alpha.png");
    //масштабируем маску альфа-смешивания планеты под заданный размер планеты
    planet_alpha=planet_alpha.scaled(planet_size,planet_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //загрузка тени планеты
    planet_shadow.load("img/planet_shadow.png");
    //масштабируем тень планеты подзаданный размер планеты
    planet_shadow=planet_shadow.scaled(planet_size,planet_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //загрузка текстурной карты ночных огней городов
    planet_lights_texture.load("img/planet_lights_texture.png");

    //масштабируемтекстурнуюкартуночныхогнейгородовподразмертекстурнойкартыпланеты
    planet_lights_texture = planet_lights_texture.scaled(planet_texture.width(), planet_texture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //загрузкамаскиальфа-смешиванияночныхогнейгородов
    planet_lights_alpha.load("img/planet_lights_alpha.png");
    //масштабируеммаскуальфа-смешиванияночныхогнейгородовподзаданныйразмерпланеты
    planet_lights_alpha=planet_lights_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //загрузка текстурной карты атмосферы
    planet_atmosphere_texture.load("img/planet_atmosphere_texture.png");

    //масштабируем текстурную карту атмосферы под заданный размер текстурной карты планеты
    planet_atmosphere_texture = planet_atmosphere_texture.scaled(planet_texture.width(), planet_texture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //загрузкамаскиальфа-смешиванияатмосферы
    planet_atmosphere_alpha.load("img/planet_atmosphere_alpha.png");

    //масштабируем маску альфа-смешивания атмосферы под заданный размер планеты + увеличенный размер шапки атмосферы
    planet_atmosphere_alpha = planet_atmosphere_alpha.scaled(planet_size + atmosphere_up_size*2, planet_size + atmosphere_up_size*2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    /*
     * загружаем текстуры новых объектов (Луны и Солнца) аналогичным образом, при этом альфа-маску-круга и альфа-маску-тени используем существующие, от планеты
     */

    //загрузкатекстурнойкартыспутникапланеты
    moon_texture.load("img/moon.png");

    //загрузкамаскиальфа-смешиванияспутника
    moon_alpha.load("img/planet_alpha.png");

    //масштабируем маску альфа-смешивания спутника планеты под заданный размер
    moon_alpha = moon_alpha.scaled(moon_size,moon_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //масштабируем тень спутника планеты под заданный размер планеты
    moon_shadow = planet_shadow.scaled(moon_size,moon_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //загрузка текстурной карты звезды
    star_texture.load("img/sun.png");

    //загрузка маски альфа-смешивания звезды
    star_alpha.load("img/planet_alpha.png");

    //масштабируеммаскуальфа-смешиваниязвездыподзаданныйразмер
    star_alpha = star_alpha.scaled(star_size,star_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //инициализацияобъектатаймера
    timer_cycle = new QTimer();

    //соединим сигнал таймера со слотом обновления экрана
    connect(timer_cycle,SIGNAL(timeout()),this,SLOT(cycle()));

    //запустим таймер
    timer_cycle -> start(20);

}

void MainWindow::cycle()
{
    //копированиеучасткатекстурывсоответствииспозициейсчетчикавращенияпланеты
    planet=planet_texture.copy(planet_rotation,0,planet_texture.height(),planet_texture.height());

    //масштабируемитоговоеизображениепланетыдозаданногоразмера
    planet=planet.scaled(planet_size,planet_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //копированиеучасткатекстурыогнейгородоввсоответствииспозициейсчетчикавращенияпланеты
    planet_lights=planet_lights_texture.copy(planet_rotation,0,planet_lights_texture.height(),planet_lights_texture.height());

    //масштабируемитоговоеизображениеогнейгородовдозаданногоразмерапланеты
    planet_lights=planet_lights.scaled(planet_size,planet_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //копированиеучасткатекстурыатмосферывсоответствииспозициейсчетчикавращенияатмосферы
    planet_atmosphere = planet_atmosphere_texture.copy(atmosphere_rotation,0,planet_atmosphere_texture.height(),planet_atmosphere_texture.height());

    //масштабируем итоговое изображение атмосферы до заданного размерапланеты + увеличение размера на размер шапки атмосферы
    planet_atmosphere = planet_atmosphere.scaled(planet_size+atmosphere_up_size*2, planet_size+atmosphere_up_size*2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //копированиеучасткатекстурывсоответствииспозициейсчетчикавращенияспутника
    //Примечание: подготовим новые объекты, аналогично планете.
    moon = moon_texture.copy(moon_rotation,0,moon_texture.height(),moon_texture.height());
    //масштабируемитоговоеизображениеспутникадозаданногоразмера
    moon = moon.scaled(moon_size,moon_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //копированиеучасткатекстурывсоответствииспозициейсчетчикавращениязвезды
    star = star_texture.copy(star_rotation,0,star_texture.height(),star_texture.height());
    //масштабируемитоговоеизображениезвездыдозаданногоразмера
    star = star.scaled(star_size,star_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //инициализируем рисовальщик для преобразования итогового изображения планеты
    QPainter painter(&planet);

    //установим режимкомпозицииальфа-смешивания-прозрачныйцветальфа-маскископируетсянаитоговоеизображение
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    //отрисовкавобъектитоговогоизображенияпланетыальфамаски
    painter.drawImage(0,0,planet_alpha);

    //инициализируем рисовальщик для преобразования итогового изображения звезды
    QPainter ps(&star);

    //установим режим композицииальфа-смешивания-прозрачныйцветальфа-маскископируетсянаитоговоеизображение
    ps.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    //отрисовка в объект итогового изображения звезды альфа маски
    ps.drawImage(0,0,star_alpha);

    //инициализируем рисовальщик для преобразования итогового изображения спутника
    QPainter pm(&moon);

    //установим режим композиции альфа-смешивания-прозрачный цвет альфа-маскис копируется на итоговое изображение
    pm.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    //отрисовка в объект итогового изображения спутника альфа маски
    pm.drawImage(0,0,moon_alpha);

    //инициализируем рисовальщик для преобразования итогового изображения ночных огней планеты
    QPainter painter2(&planet_lights);

    //установим режим композиции альфа-смешивания-прозрачный цвет альфа-маски скопируется на итоговое изображение
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    //отрисовка в объектизображения планеты альфа маски для отсечения углов
    painter2.drawImage(0,0,planet_alpha);

    //отцентрируемсцену
    painter2.translate(planet_size/2,planet_size/2);
    //повернемсценудляповоротаальфамаскисогласноосвещению

    painter2.rotate(orbital_rotation);
    //отрисовкавобъектитоговогоизображенияогнейпланетыальфамаски
    painter2.drawImage(-planet_size/2,-planet_size/2,planet_lights_alpha);

    //инициализируем рисовальщик для преобразования итогового изображения атмосферы планеты
    QPainter painter3(&planet_atmosphere);

    //установим режим композиции альфа-смешивания-прозрачный цвет альфа-маски скопируется на итоговое изображение
    painter3.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    //отрисовкавобъектитоговогоизображенияатмосферыпланетыальфамаски
    painter3.drawImage(0,0,planet_atmosphere_alpha);
    //увеличимсчетчиквращенияорбиты
    orbital_rotation+=orbital_speed;
    //обнулимсчетчикорбиты,еслипрошлиполныйкруг
    if(orbital_rotation>360) orbital_rotation=0;
    //увеличимсчетчиквращенияпланетынавеличинускорости
    planet_rotation+=speed_planet_rotation;
    //если значение счетчика выходит за рамки размера текстуры, то обнулить счетчик
    if (planet_rotation+planet_texture.height()>=planet_texture.width()) planet_rotation=0;
    //увеличим счетчик вращения атмосферы планеты на величину скорости
    atmosphere_rotation += speed_atmosphere_rotation;
    //если значение счетчика выходит за рамки размера текстуры, то обнулить счетчик
    if (atmosphere_rotation + planet_atmosphere_texture.height() >= planet_atmosphere_texture.width()) atmosphere_rotation =0;

    // Примечание: аналогично установим счетчики вращения Солнца и Луны,а также счетчик вращения орбиты Луны.

    // увеличим счетчик вращения спутника на величину скорости
    moon_rotation += speed_moon_rotation;

    //если значение счетчика выходитзарамкиразмератекстуры,тообнулитьсчетчик
    if (moon_rotation+moon_texture.height() >= moon_texture.width()) moon_rotation = 0;

    // увеличим счетчик вращения планеты на величину скорости
    star_rotation += speed_star_rotation;

    //если значение счетчика выходит за рамки размера текстуры, то обнулить счетчик
    if (star_rotation + star_texture.height()>=star_texture.width()) star_rotation = 0;

    // увеличим счетчик вращения орбиты спутника
    orbital_moon_rotation += orbital_moon_speed;
    //обнулим счетчик орбитыспутника,еслипрошлиполныйкруг
    if (orbital_moon_rotation > 360) orbital_moon_rotation = 0;

    //обновим экран
    update();
}


// отрисовка экрана
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //установим границы отображения для рисовальщика
    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(), ui->screen->geometry().width(), ui->screen->geometry().height());

    //масштабируем звездный фон
    star_background = star_background.scaled(ui->screen->geometry().width(), ui->screen->geometry().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    //и выведем его на экран
    painter.drawImage(0, 0, star_background);

    painter.save();

    //сместим начало координат сцены к центру виджета screen
    painter.translate(ui->screen->geometry().width()/2 + x_axis, ui->screen->geometry().height()/2 + y_axis);

    //применим масштабирование для сцены
    painter.scale(scale_scene,scale_scene);

    // выводим изображение звезды
    painter.drawImage(-star_size/2, -star_size/2, star);

    //определим перо для отображения
    QPen pen;

    pen.setColor(Qt::darkGreen);
    pen.setWidth(1);
    painter.setPen(pen);

    //выведемокружностьорбиты
    painter.drawEllipse(-orbital_size,-orbital_size,orbital_size*2,orbital_size*2);

    //повернемсистемукоординатсогласноуглуорбитыпланеты
    painter.rotate(orbital_rotation);

    //сместимначалокоординатсценынаорбиту
    painter.translate(orbital_size,0);

    //повернем систему координатнауголпротивоположныйорбите,чтобыизображениепланетыневращалось
    painter.rotate(-orbital_rotation);

    //выводим изображение планеты
    painter.drawImage(-planet_size/2, -planet_size/2, planet);

    //выводатмосферы
    painter.drawImage(-(planet_size+atmosphere_up_size)/2, -(planet_size+atmosphere_up_size)/2, planet_atmosphere);

    //вернемсистемукоординатнауголорбиты,чтобытеньпланетывращалась
    painter.rotate(orbital_rotation);

    //выводтенипланеты
    painter.drawImage(-planet_size/2,-planet_size/2,planet_shadow);

    //повернем системукоординатнауголпротивоположныйорбите,чтобыизображениеночныхогнейневращалось
    painter.rotate(-orbital_rotation);

    //вывод ночных огней
    painter.drawImage(-planet_size/2,-planet_size/2,planet_lights);

    //выведемокружностьорбитыспутника
    painter.drawEllipse(-orbital_moon_size, -orbital_moon_size, orbital_moon_size*2, orbital_moon_size*2);

    //повернемсистемукоординатсогласноуглуорбитыспутника
    painter.rotate(orbital_moon_rotation);

    //сместимначалокоординатсценынаорбитуспутника
    painter.translate(orbital_moon_size, 0);

    //повернемсистемукоординатобратноуглуорбитыспутника
    painter.rotate(-orbital_moon_rotation);

    //выводимизображениеспутника
    painter.drawImage(-moon_size/2,-moon_size/2,moon);

    //выведем тень спутника с учетом орбиты планеты
    painter.rotate(orbital_rotation);

    //вывод тени спутника
    painter.drawImage(-moon_size/2,-moon_size/2,moon_shadow);

    //восстановим состояние сцены
    painter.restore();

    //вывод таблички с название мобъекта
    if (show_info)
    {
        pen.setColor(Qt::darkGreen);
        pen.setWidth(2);
        QBrush brush;
        brush.setColor(QColor(0,255,0,120));
        brush.setStyle(Qt::SolidPattern);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(coord_info_x,coord_info_y,100,20);
        pen.setColor(QColor(0,0,0,255));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawText(coord_info_x,coord_info_y,100,20,Qt::AlignCenter,text_info);
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{        
    if (event->key() == Qt::Key_Space)
    {
        //ui->lineEdit->clear();
    }
}

// Обработчик мыши
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //отобразим координату X
    //ui->lineEdit_x->setText(QString::number(event->x()));
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    this->update();

    if (event->type() == QEvent::MouseButtonPress)
    {
        return true;

        //отпусканиекнопокмыши
        if (event->type()==QEvent::MouseButtonRelease)
        {

            return true;
        };

        //проверим состояние колесика
        if (event->type()==QEvent::Wheel)
        {

            return true;
        };

        //движение мыши

        if (event->type()==QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = (QMouseEvent*)event;

            return true;
        };

        return false;

    }

}

