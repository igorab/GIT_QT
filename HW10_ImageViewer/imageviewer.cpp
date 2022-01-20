#include "imageviewer.h"
#include "ui_ImageViewer.h"

///
/// \brief ImageViewer::ImageViewer
/// constructor
/// \param parent
///
ImageViewer::ImageViewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    InitialPicture.load("img/planet_alpha.png");
    /*
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    //createActions();
    //createMenus();

    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);
    */
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                        tr("Open File"), QDir::currentPath());
    /*
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
            */
}

void ImageViewer::print()
{
    // Q_ASSERT(imageLabel->pixmap());
}

void ImageViewer::zoomIn()
{
    //scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    //scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
    /*
    bool fitToWindow = fitToWindowAct->isChecked();

         scrollArea->setWidgetResizable(fitToWindow);

         if (!fitToWindow) {
             normalSize();
         }

         updateActions();
         */
}

void ImageViewer::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
                 tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
                    "and QScrollArea to display an image. QLabel is typically used "
                    "for displaying a text, but it can also display an image. "
                    "QScrollArea provides a scrolling view around another widget. "
                    "If the child widget exceeds the size of the frame, QScrollArea "
                    "automatically provides scroll bars. </p><p>The example "
                    "demonstrates how QLabel's ability to scale its contents "
                    "(QLabel::scaledContents), and QScrollArea's ability to "
                    "automatically resize its contents "
                    "(QScrollArea::widgetResizable), can be used to implement "
                    "zooming and scaling features. </p><p>In addition the example "
                    "shows how to use QPainter to print an image.</p>"));
}


void ImageViewer::on_PushButtonFileOpen_clicked()
{
    QFileDialog dialog(this);

    dialog.setNameFilter(tr("Images(*.png *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Images"), "C:", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
    {
        QImage image(fileName);

        QPainter qPainter(&InitialPicture);

        //qPainter.fillRect(0, 0, 128, 128, Qt::green);
        //qPainter.begin(ui->Screen);


        qPainter.drawImage(0, 0, image);
        qPainter.drawLine(0,0,100,100);
        //ui->Screen->set
        //QPixmap pixmap = QPixmap::fromImage(image);
        //ui->LableFileOpen->setPixmap(pixmap);

        update();

        //qPainter.save();

    }
}

void ImageViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setViewport(ui->Screen->geometry().x(), ui->Screen->geometry().y(), ui->Screen->geometry().width(), ui->Screen->geometry().height());

    painter.drawImage(0, 0, InitialPicture);

    painter.drawLine(0,0,100,100);
    painter.save();
    painter.restore();
}

