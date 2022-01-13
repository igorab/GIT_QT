#include "imageviewer.h"
#include "ui_ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}


void ImageViewer::on_PushButtonFileOpen_clicked()
{
    QFileDialog dialog(this);

    dialog.setNameFilter(tr("Images(*.png *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this, "Open Images", "C:");

    if (!fileName.isEmpty())
    {
        QImage image(fileName);
    }
}

