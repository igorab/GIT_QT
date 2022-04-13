#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H
#include <QtGlobal>
#include<QtCore>
#include <QMainWindow>
#include <QPrinter>
#include <QPrintDialog>

#include <QPainter>
#include <QFileDialog>


#include <QMessageBox>

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QScrollBar>


QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
QT_END_NAMESPACE

/*
Создать программу, которая выводит любое изображение на экран и позволяет:
1. Масштабировать колесом мыши при зажатии клавиши CTRL.
2. Прокручивать вверх/вниз колесом мыши.
3. Перетаскивать изображение мышью при зажатии клавиши ALT и левой кнопки мыши.Дополнительный функционал (по желанию):
4. Клавиши ↑ и ↓ изменяют яркость изображения от 0 до 100%.5. Клавиши → и ← вращают изображение на 90°Для самых продвинутых:
6. Кнопка "Сохранить" производит сохранение полученного в результате изменения яркости и вращения изображение во внешний файл.
*/

// http://doc.crossplatform.ru/qt/4.7.x/widgets-imageviewer.html

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:

    ImageViewer();

    QImage InitialPicture;

private slots:

    void open();
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void rotateCW();
    void rotateCCW();

private:

    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    // перетаскивать изображение мышью
    //void moveImage();
    // изменить яркость изображения
    //void changeImageBrightness();
    // повернуть изображение
    void rotateImage(double angle = 45);
    // сохранить измененное изображение во внешний файл
    //void saveImage();

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *clockwiseAct;
    QAction *counterclockwiseAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

};
#endif // IMAGEVIEWER_H
