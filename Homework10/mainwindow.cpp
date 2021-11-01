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


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

#ifdef __linux__
    //код для Linux
#elif __sun
    // дляSolaris
#elif _WIN32
    //код для windows
#else
#endif

    switch (event->key())
    {
        case Qt::Key_A:
            ui->lineEdit->setText("Key A Pressed");
            break;

        case Qt::Key_B:
            ui->lineEdit->setText("Key B Pressed");
            break;

        case Qt::Key_C:
            ui->lineEdit->setText("Key C Pressed");
            break;

        case Qt::Key_Space:
            ui->lineEdit->clear();
            break;
    }

    //модификаторCtrl
    if (event->modifiers()==Qt::CTRL)
    {
        //определяемклавишу
        switch(event->key())
        {
            case Qt::Key_A:
                ui->lineEdit->setText("KeyA+Ctrl pressed!");
                break;
            case Qt::Key_B:
                ui->lineEdit->setText("KeyB+Ctrl pressed!");
                break;
            case Qt::Key_C:
                ui->lineEdit->setText("KeyC+Ctrl pressed!");
                break;
        }
    }

    //обамодификатора Ctrl+Alt,обратитевниманиенаспособнаписанияусловия!
    if ((event->modifiers() & Qt::CTRL) && (event->modifiers()  &Qt::ALT))
    {
        //определяемклавишу
        switch (event->key()) {
            case Qt::Key_A:
                ui->lineEdit->setText("Key A + Ctrl+Alt pressed!");
                break;
            case Qt::Key_B:
                ui->lineEdit->setText("KeyB+Ctrl+Alt pressed!");
                break;
            case Qt::Key_C:
                ui->lineEdit->setText("KeyC+Ctrl+Alt pressed!");
            break;
        }
    }

    if (event->key() == Qt::Key_Space)
    {
        ui->lineEdit->clear();
    }



}

// Обработчик мыши
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //отобразим координату X
    ui->lineEdit_x->setText(QString::number(event->x()));

    //отобразим координату Y
    ui->lineEdit_y->setText(QString::number(event->y()));
    //определим нажатие кнопки
    QString temp_state_str;

    if (event->button()==Qt::LeftButton)
        temp_state_str+="left mouse button is pressed!;";

    if (event->button()==Qt::RightButton)
        temp_state_str+="right mouse button is pressed!;";

    if (event->button()==Qt::MiddleButton)
        temp_state_str+="middle mouse button is pressed!;";

    //выведемввидетекста,какиекнопкинажатынамыши

    ui->lineEdit_buttons->setText(temp_state_str);

    //проверим состояние колесика
    if (event->type()==QEvent::Wheel)
    {
        QWheelEvent *wheel = (QWheelEvent*)event;

        int scroll = 50;

        if (wheel->delta() > 0 && scroll < 99)
            scroll +=1;
        else if (scroll > 0)
            scroll -=1;

        //выведем значения на скроллбар
        ui->horizontalSlider_scroll->setValue(scroll);
        ui->label_scroll->setNum(scroll);
    }

}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    this->update();

    if (event->type() == QEvent::MouseButtonPress)
    {
        QString temp_state_str;

        QMouseEvent *mouseEvent =  (QMouseEvent*) event;

        //левая кнопка мыши
        if (mouseEvent->button()==Qt::LeftButton)
            temp_state_str += "leftmousebuttonispressed!;";

        if (mouseEvent->button() == Qt::RightButton)
            temp_state_str += "rightmousebuttonispressed!;";

        if (mouseEvent->button()==Qt::MiddleButton)
            temp_state_str += "middlemousebuttonispressed!;";

        // выведем в виде текста состояние кнопок мыши
        ui->lineEdit_buttons->setText(temp_state_str);

        return true;

        //отпусканиекнопокмыши
        if (event->type()==QEvent::MouseButtonRelease)
        {
            QString temp_state_str;
            QMouseEvent *mouseEvent=(QMouseEvent*)event;
            //левая кнопка мыши
            if (mouseEvent->button()==Qt::LeftButton)
                temp_state_str += "leftmousebuttonisrealised!;";

            if (mouseEvent->button()==Qt::RightButton)
                temp_state_str += "rightmousebuttonisrealised!;";

            if (mouseEvent->button()==Qt::MiddleButton)
                temp_state_str += "middlemousebuttonisrealised!;";

            //выведем в виде текста состояние кнопок мыши
            ui->lineEdit_buttons->setText(temp_state_str);

            return true;
        };

        //проверим состояние колесика
        if (event->type()==QEvent::Wheel)
        {
            QWheelEvent *wheel = (QWheelEvent*)event;

            int encoder = wheel->delta();

            if (encoder > 0 && ui->horizontalSlider_scroll->value() < 99)
            {
                ui->horizontalSlider_scroll->setValue(ui->horizontalSlider_scroll->value()+1);

                ui->label_scroll->setNum(ui->horizontalSlider_scroll->value());
            }
            else
            {
                ui->horizontalSlider_scroll->setValue(ui->horizontalSlider_scroll->value()-1);
                ui->label_scroll->setNum(ui->horizontalSlider_scroll->value());
            };

            return true;
        };

        //движение мыши

        if (event->type()==QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = (QMouseEvent*)event;

            //отобразим координату X
            ui->lineEdit_x->setText(QString::number(mouseEvent->pos().x()));

            //отобразим координату Y
            ui->lineEdit_y->setText(QString::number(mouseEvent->pos().y()));
            return true;
        };

        return false;

    }

}

