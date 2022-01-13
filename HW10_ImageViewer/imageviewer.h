#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QPainter>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:

    ImageViewer(QWidget *parent = nullptr);

    ~ImageViewer();

private slots:
    void on_PushButtonFileOpen_clicked();

private:
    Ui::ImageViewer *ui;


};
#endif // IMAGEVIEWER_H
