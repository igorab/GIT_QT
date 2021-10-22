#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

