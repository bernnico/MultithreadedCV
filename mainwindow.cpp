#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef USE_QTHREAD
    connect(&processor, SIGNAL(inDisplay(QPixmap)),
            ui->inVideo, SLOT(setPixmap(QPixmap)));

    connect(&processor, SIGNAL(outDisplay(QPixmap)),
            ui->outVideo, SLOT(setPixmap(QPixmap)));

    processor.start();
#else
    processor = new VideoProcessor();
    processor->moveToThread(new QThread(this));

    connect(processor->thread(), SIGNAL(started()),
            processor, SLOT(startVideo()));

    connect(processor->thread(), SIGNAL(finished()),
            processor, SLOT(deleteLater()));

    connect(processor, SIGNAL(inDisplay(QPixmap)),
            ui->inVideo, SLOT(setPixmap(QPixmap)));

    connect(processor, SIGNAL(outDisplay(QPixmap)),
            ui->outVideo, SLOT(setPixmap(QPixmap)));

    processor->thread()->start();
#endif /* USE_QTHREAD */
}

MainWindow::~MainWindow()
{
#ifdef USE_QTHREAD
    processor.requestInterruption();
    processor.wait();
#else
    processor->stopVideo();
    processor->thread()->quit();
    processor->thread()->wait();
#endif /* USE_QTHREAD */

    delete ui;
}
